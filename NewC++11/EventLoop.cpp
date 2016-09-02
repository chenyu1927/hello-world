#include "EventLoop.h"
#include <sys/eventfd.h>
#include "Channel.h"
#include "Epoller.h"
#include "TimerQueue.h"
#include <unistd.h>

namespace
{

__thread EventLoop* t_loopInThisThread = nullptr;

const int kEpollTimeMs = 10000;

int createEventFd()
{
	int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
	if (evtfd < 0)
	{
		fprintf(stderr, "create eventfd error\n");
		abort();
	}

	return evtfd;
}

}

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
	return t_loopInThisThread;
}

EventLoop::EventLoop()
	: looping_(false), quit_(false), 
	  eventHandling_(false), callingPendingFunctors_(false),
	  iteration_(0), threadId_(CurrentThread::tid()),
	  epoller_(new Epoller(this)), timerQueue_(new TimerQueue(this)), wakeupFd_(createEventFd()),
	  wakeupChannel_(new Channel(this, wakeupFd_)), currentActiveChannel_(nullptr)
{
	if (t_loopInThisThread)
	{
		fprintf(stderr, "Another EventLoop exists int this Thread\n");
		abort();
	}
	else
	{
		t_loopInThisThread = this;
	}

	wakeupChannel_->setReadCallback(std::bind(&EventLoop::handleRead, this));
	wakeupChannel_->enableReading();
}

EventLoop::~EventLoop()
{
	wakeupChannel_->disableAll();
	wakeupChannel_->remove();
	::close(wakeupFd_);
	t_loopInThisThread = nullptr;
}


void EventLoop::loop()
{
	assert(!looping_);
	assertInLoopThread();

	looping_ = true;
	quit_ = false;

	while(!quit_)
	{
		activeChannels_.clear();
		pollReturnTime_ = epoller_->poll(kEpollTimeMs, &activeChannels_);
		
		eventHandling_ = true;
		for(auto iter = activeChannels_.begin(); iter < activeChannels_.end(); ++ iter)
		{
			currentActiveChannel_ = *iter;
			currentActiveChannel_->handleEvent(pollReturnTime_);
		}
		currentActiveChannel_ = nullptr;
		eventHandling_ = false;
		doPendingFunctors();
	}
}

void EventLoop::doPendingFunctors()
{
	std::vector<Functor> functors;
	callingPendingFunctors_ = true;

	{
		MUTEX_GUARD(mutex_, obj);
		functors.swap(pendingFunctors_);
	}

	for (size_t i = 0; i < functors.size(); ++ i)
	{
		functors[i]();
	}
	callingPendingFunctors_ = false;
}

void EventLoop::quit()
{
	quit_ = true;
	if (!isInLoopThread())
	{
		wakeup();
	}
}

void EventLoop::runInLoop(Functor&& cb)
{
	if (isInLoopThread())
	{
		cb();
	}
	else
	{
		queueInLoop(std::move(cb));
	}
}

void EventLoop::queueInLoop(Functor&& cb)
{
	{
		MUTEX_GUARD(mutex_, obj);
		pendingFunctors_.push_back(std::move(cb));
	}

	if (!isInLoopThread() || callingPendingFunctors_)
	{
		wakeup();
	}
}

void EventLoop::wakeup()
{
	uint64_t one = 1;
	ssize_t n = ::write(wakeupFd_, &one, sizeof one);
	if (n != sizeof one)
	{
		fprintf(stderr, "EventLoop wakeup() write error!");
	}
}

void EventLoop::handleRead()
{
	uint64_t one = 0;
	ssize_t n = ::read(wakeupFd_, &one, sizeof one);
	if (n != sizeof one)
	{
		fprintf(stderr, "EventLoop handleEvent() read size error");
	}
}


void EventLoop::updateChannel(Channel* channel)
{
	assert(channel->ownerLoop() == this);
	assertInLoopThread();
	epoller_->updateChannel(channel);
//	int events = channel->events();

}

void EventLoop::removeChannel(Channel* channel)
{
	assert(channel->ownerLoop() == this);
	assertInLoopThread();

	if (eventHandling_)
	{
		assert(currentActiveChannel_ == channel || 
				std::find(activeChannels_.begin(), activeChannels_.end(), channel) == activeChannels_.end());

	}
	epoller_->removeChannel(channel);
}

bool EventLoop::hasChannel(Channel* channel)
{
	assert(channel->ownerLoop() == this);
	assertInLoopThread();

	return epoller_->hasChannel(channel);
}

void EventLoop::abortNotInLoopThread()
{
	
}

TimerId EventLoop::runAt(const Timestamp& time, TimerCallback&& cb)
{
	assert(looping_ && !quit_);
	return timerQueue_->addTimer(std::move(cb), time, 0.0);
}

TimerId EventLoop::runAfter(double delay, TimerCallback&& cb)
{
	Timestamp time(addTime(Timestamp::now(), delay));
	return timerQueue_->addTimer(std::move(cb),time, 0.0);
}

TimerId EventLoop::runEvery(double interval, TimerCallback&& cb)
{
	return timerQueue_->addTimer(std::move(cb), Timestamp::now(), interval);
}


