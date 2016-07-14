#include "EventLoop.h"
#include <boost/bind.hpp>
#include <sys/eventfd.h>
#include "Poll.h"
#include "Channel.h"
int createEventFd()
{
	int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
	if (evtfd < 0)
	{
		//log
		abort();
	}

	return evtfd;
}

static const int kPollTimeMs = 10000;

EventLoop::EventLoop()
	: looping_(false),
	  quit_(false),
	  eventHandling_(false),
	  wakeupFd_(createEventFd()),
	  wakeupChannel_(new Channel(this, wakeupFd_)),
	  poller_(Poller::newDefaultPoller(this)),
	  currentActiveChannel_(0)
{
	wakeupChannel_->setReadCallBack(
			boost::bind(&EventLoop::handleRead, this));
	wakeupChannel_->enableReading();
}

EventLoop::~EventLoop()
{
	wakeupChannel_->disableAll();
	wakeupChannel_->remove();

	::close(wakeupFd_);
}

void EventLoop::loop()
{
	assert(!looping_);
	looping_ = true;
	quit_ = false;

	while (!quit_)
	{
		activeChannels_.clear();
		Timestamp pollReturnTime_ = poller_->poll(kPollTimeMs, activeChannels_);
		
		eventHandling_ = true;
		for (ChannelList::iterator iter = activeChannels_.begin();
				iter < activeChannels_.end(); ++ iter)
		{
			currentActiveChannel_ = *iter;
			currentActiveChannel_->handleEvent();
		}

		currentActiveChannel_ = 0;
		eventHandling_ = false;
	}

	looping_ = false;
}

void EventLoop::quit()
{
	quit_ = true;

}

void EventLoop::updateChannel(Channel* channel)
{
	poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel* channel)
{
	if (eventHandling_)
	{
		assert(currentActiveChannel_ == channel ||
				std::find(activeChannels_.begin(), activeChannels_.end(), channel) == activeChannels_.end());
		
	}

	poller_->removeChannel(channel);
}

void EventLoop::wakeup()
{
	int64_t one = 1;
	ssize_t n = write(wakeupFd_, &one, sizeof one);

	if (n != sizeof one)
	{
		//log error
	}
}

void EventLoop::handleRead()
{
	int64_t one = 1;
	ssize_t n = read(wakeupFd_, &one, sizeof one);

	if (n != sizeof one)
	{
		//log error
	}
}

void EventLoop::runInLoop(const Functor& cb)
{
	if (isInLoopThread())
	{
		cb();
	}
	else
	{
		queueInLoop(cb);
	}
}

void EventLoop::queueInLoop(const Functor& cb)
{
	{
		MUTEX_GUARD(obj, mutex_);
		pendingFunctors_.push_back(cb);
	}

	if (!isInLoopThread() || callingPendingFunctors_)
	{
		wakeup();
	}
}
