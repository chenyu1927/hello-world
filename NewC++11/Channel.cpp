#include "Channel.h"
#include <sys/epoll.h>
//#include <poll.h>
#include "EventLoop.h"
#include <assert.h>

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop* loop, int fd)
	: loop_(loop), fd_(fd), events_(kNoneEvent),
	  revents_(kNoneEvent), index_(-1),
	  loghup_(false), tied_(false),
	  eventHandling_(false), addedToLoop_(false)
{

}

Channel::~Channel()
{
	assert(!eventHandling_);
	assert(!addedToLoop_);
	if (loop_->isInLoopThread())
	{
		fprintf(stderr, "channel destroy fd = %d\n", fd());
		assert(!loop_->hasChannel(this)); // has remove from this loop
	}
}


void Channel::tie(const std::shared_ptr<void>& obj)
{
	tie_ = obj;
	tied_ = true;
}

void Channel::_update()
{
	addedToLoop_ = true;
	loop_->updateChannel(this);
}

void Channel::remove()
{
	assert(isNoneEvent());
	addedToLoop_ = false;
	loop_->removeChannel(this);
}

void Channel::handleEvent(Timestamp receiveTime)
{
	std::shared_ptr<void> guard;
	if (tied_)
	{
		guard = tie_.lock();
		if (guard)
		{
			handleEventWithGuard(receiveTime);
		}
	}
	else
	{
		handleEventWithGuard(receiveTime);
	}
}


void Channel::handleEventWithGuard(Timestamp receviceTime)
{
	eventHandling_ = true;
	if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
	{
		if (closeCallback_) closeCallback_();
	}

/*	if (revents_ & EPOLLNVAL)
	{
		fprintf(stderr, "fd epoll EPOLLNVAL")
	}*/
	
	if (revents_ & EPOLLERR)
	{
		if (errorCallback_) errorCallback_();
	}

	if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLHUP))
	{
		if (readCallback_) readCallback_(receviceTime);
	}

	if (revents_ & EPOLLOUT)
	{
		if (writeCallback_) writeCallback_();
	}

	eventHandling_ = false;
}




