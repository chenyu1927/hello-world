#ifndef CHANNEL_H_H
#define CHANNEL_H_H

#include <boost/noncopyable.hpp>
#include <functional>
#include <memory>
#include "Timestamp.h"

class EventLoop;

class Channel : boost::noncopyable
{
public:
	typedef std::function<void()> EventCallback;
	typedef std::function<void(Timestamp)> ReadEventCallback;
//	typedef std::function<void ()> EventCallback;

	Channel(EventLoop* loop, int fd);
	~Channel();

	void handleEvent(Timestamp receviceTime);

	void setReadCallback(ReadEventCallback&& cb)
	{ readCallback_ = cb; }
	void setWriteCallback(EventCallback&& cb)
	{ writeCallback_ = cb; }
	void setCloseCallback(EventCallback&& cb)
	{ closeCallback_ = cb; }

	void tie(const std::shared_ptr<void>&);
	int fd() const { return fd_; }
	int events() const { return events_; }
	void set_revents(int revt) { revents_ = revt; }

	bool isNoneEvent() const { return events_ == kNoneEvent; }
	void enableReading() { events_ |= kReadEvent; _update(); }
	void disableReading() { events_ &= ~kReadEvent; _update(); }
	void enableWriting() { events_ |= kWriteEvent; _update(); }
	void disableWriting() { events_ &= ~kWriteEvent; _update(); }
	void disableAll() { events_ = kNoneEvent; _update(); }
	bool isReading() const { return events_ & kReadEvent; }
	bool isWriting() const { return events_ & kWriteEvent; } 

	int index() const { return index_; }
	void set_index(int index) { index_ = index; }

	EventLoop* ownerLoop() { return loop_; }
	void remove();

private:
	static const int kNoneEvent;
	static const int kReadEvent;
	static const int kWriteEvent;

	void _update();
	void handleEventWithGuard(Timestamp);

	EventLoop* loop_;
	const int  fd_;
	int		   events_;

	int        revents_;
	int 	   index_;
	bool       loghup_;

	std::weak_ptr<void> tie_;
	bool       tied_;
	bool       eventHandling_;
	bool       addedToLoop_;

	ReadEventCallback readCallback_;
	EventCallback	  writeCallback_;
	EventCallback	  closeCallback_;
	EventCallback	  errorCallback_;
};






#endif /* CHANNEL_H_H */
