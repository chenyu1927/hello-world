#include "Channel.h"
#include "EventLoop.h"
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop, int fd)
	: loop_(loop),
	  fd_(fd),
	  events_(0),
	  revents_(0),
	  index_(-1),
	  tied_(0),
	  eventHandling_(0),
	  addedToLoop_(0)
{

}

Channel::~Channel()
{

}

void Channel::update()
{
	addedToLoop_ = true;
	loop_->updateChannel(this);
}

void Channel::remove()
{
	addedToLoop_ = false;
	loop_->removeChannel(this);
}

void Channel::handleEvent()
{
	boost::shared_ptr<void> guard;
	if (tied_)
	{
		guard = tie_.lock();
		if (guard)
		{
			handleEventWithGuard();
		}
	}
	else
	{
		handleEventWithGuard();
	}
}

void Channel::handleEventWithGuard()
{
	eventHandling_ = true;
	if ((revents_ & POLLHUP) && !(revents_ & POLLIN))
	{
		if (closeCallback_) closeCallback_();	
	}

	if (revents_ & (POLLIN | POLLPRI | POLLRDHUP))
	{
		if (readCallback_) readCallback_();

	}

	if (revents_ &  POLLOUT)
	{
		if (writeCallback_) writeCallback_();
	}
	eventHandling_ = false;
}

/*inline void Channel::setReadCallBack(const EventCallBack& readCallBack)
{
	readCallback_ = readCallBack;
}*/

inline void Channel::setWriteCallBack(const EventCallBack& writeCallBack)
{
	writeCallback_ = writeCallBack;
}

inline void Channel::setCloseCallBack(const EventCallBack& closeCallBack)
{
	closeCallback_ = closeCallBack;
}
