#include "TimerQueue.h"
#include "Timer.h"
#include "TimerId.h"
#include "EventLoop.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <strings.h>

namespace ext
{
	int createTimerfd()
	{
		int fd = ::timerfd_create(CLOCK_MONOTONIC,
				TFD_NONBLOCK | TFD_CLOEXEC);
		if (fd < 0)
		{
			fprintf(stderr, "timerfd_create error\n");
			abort();
		}
	}

	struct timespec howMuchTimeFromNow(Timestamp when)
	{
		int microseconds = when.microSecondsSinceEpoch() -
			Timestamp::now().microSecondsSinceEpoch();
		if (microseconds < 100)
		{
			microseconds = 100;
		}

		struct timespec ts;
		ts.tv_sec = static_cast<time_t>(microseconds / Timestamp::kMicroSecondsPerSecond);
		ts.tv_nsec = static_cast<long>((microseconds % Timestamp::kMicroSecondsPerSecond) * 1000);

		return ts;
	}

	void readTimerfd(int timerfd, Timestamp now)
	{
		uint64_t howmany;
		ssize_t n = ::read(timerfd, &howmany, sizeof howmany);
		if (n != sizeof howmany)
		{
			fprintf(stderr, "TimerQueue::handleRead() reads error\n");
			abort();
		}
	}

	void resetTimerfd(int timerfd, Timestamp expiration)
	{
		struct itimerspec newValue;
		struct itimerspec oldValue;

		bzero(&newValue, sizeof newValue);
		bzero(&oldValue, sizeof oldValue);

		newValue.it_value = howMuchTimeFromNow(expiration);
		int ret = ::timerfd_settime(timerfd, 0, &newValue, &oldValue);
		if (ret)
		{

		}
	}
}

TimerQueue::TimerQueue(EventLoop* loop)
	: loop_(loop),
	  timerfd_(ext::createTimerfd()),
	  timerfdChannel_(loop_, timerfd_),
	  callingExpiredTimers_(false)
{
	assert(timerfd_ >= 0);
	timerfdChannel_.setReadCallback(std::bind(&TimerQueue::handleRead, this));
	timerfdChannel_.enableReading();
}

TimerQueue::~TimerQueue()
{
	timerfdChannel_.disableAll();
	timerfdChannel_.remove();
	
	::close(timerfd_);

	for (auto iter : timers_)
	{
		delete iter.second;
	}
}

TimerId TimerQueue::addTimer(TimerCallback&& cb, Timestamp when, double interval)
{
	Timer* timer(new Timer(std::move(cb), when, interval));
	loop_->runInLoop(std::bind(&TimerQueue::addTimerInLoop, this, timer));

	return TimerId(timer, timer->numCreated());
}

void TimerQueue::cancleTimer(TimerId timerId)
{
	loop_->runInLoop(std::bind(&TimerQueue::cancleTimerInLoop, this, timerId));

}

void TimerQueue::cancleTimerInLoop(TimerId timerId)
{
	loop_->assertInLoopThread();
	ActiveTimer timer(timerId.timer_, timerId.sequeue_);
//	assert(activeTimers_.find(timer) != activeTimers_.end());
	assert(activeTimers_.size() == timers_.size());
	auto it = activeTimers_.find(timer);
	if (it != activeTimers_.end())
	{
		size_t n = timers_.erase(Entry(it->first->expiration(), it->first));
		assert(n == 1);
		delete it->first;
		activeTimers_.erase(it);
	}
	else if (callingExpiredTimers_)
	{
		cancleTimers_.insert(timer);
	}
	assert(activeTimers_.size() == timers_.size());
}

void TimerQueue::addTimerInLoop(Timer* timer)
{
	loop_->assertInLoopThread();
	bool earliestChanged = insert(timer);

	if (earliestChanged)
	{
		ext::resetTimerfd(timerfd_, timer->expiration());
	}
}

bool TimerQueue::insert(Timer* timer)
{
	loop_->assertInLoopThread();
	assert(timers_.size() == activeTimers_.size());
	bool earliestChanged = false;

	Timestamp when = timer->expiration();
	auto iter = timers_.begin();
	if (iter == timers_.end() || when < iter->first)
	{
		earliestChanged = true;
	}

	{
		auto result = timers_.insert(std::make_pair(when, timer));
		assert(result.second);
	}

	{
		auto result = activeTimers_.insert(ActiveTimer(timer, timer->sequeue()));
		assert(result.second);
	}

	assert(timers_.size() == activeTimers_.size());
	return earliestChanged;
}	



void TimerQueue::handleRead()
{
	loop_->assertInLoopThread();
	Timestamp now = Timestamp::now();
	
	ext::readTimerfd(timerfd_, now);

	std::vector<Entry> expire = getEntry(now);

	for (auto&& iter : expire)
	{
		iter.second->run();
	}

	reset(expire, now);
}


std::vector<TimerQueue::Entry> TimerQueue::getEntry(Timestamp now)
{
	assert(timers_.size() == activeTimers_.size());

	std::vector<TimerQueue::Entry> expired;

	Entry sentry(now, reinterpret_cast<Timer*>(UINTPTR_MAX));

	auto end = timers_.lower_bound(sentry);
	assert(end == timers_.end() || now < end->first);

	std::copy(timers_.begin(), end, std::back_inserter(expired));

	timers_.erase(timers_.begin(), end);

	for (auto iter : expired)
	{
		TimerQueue::ActiveTimer timer(iter.second, iter.second->sequeue());
		ssize_t n = activeTimers_.erase(timer);
		assert(n == 1);
	}

	return expired;
}

void TimerQueue::reset(std::vector<TimerQueue::Entry> expired, Timestamp  now)
{
	for (auto iter : expired)
	{
		ActiveTimer timer(iter.second, iter.second->sequeue());
		if (iter.second->repeat() && 
				cancleTimers_.find(timer) == cancleTimers_.end())
		{
			iter.second->restart(now);
			//timers_.insert(iter);
			//activeTimers_.insert(timer);
			insert(iter.second);
		}
		else
		{
			delete iter.second;
		}
	}

	Timestamp time;
	if (!timers_.empty())
	{
		time = timers_.begin()->second->expiration();
	}

	if (time.valid())
	{
		ext::resetTimerfd(timerfd_, time);
	}
}
