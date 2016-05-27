#ifndef CHANNEL_H_H
#define CHANNEL_H_H

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <sys/poll.h>
//#include "EventLoop.h"
class EventLoop;

class Channel : boost::noncopyable
{
public:
	typedef boost::function<void()> EventCallBack;
//	typedef boost::function<void()>

	Channel(EventLoop* loop, int fd);
	~Channel();

	void remove();

	void handleEvent();
	
	void setReadCallBack(const EventCallBack& readCallBack)
	{
		readCallback_ = readCallBack;
	}

	void setWriteCallBack(const EventCallBack& writeCallBack);
	void setCloseCallBack(const EventCallBack& closeCallBack);

	inline void setRevents(int rvt) { revents_ = rvt; }
	inline int getEvents() { return events_; }

	void enableReading() { events_ |= kReadEvent; update(); }
	void disableReading() { events_ &= ~kReadEvent; update(); }

	void enableWriting() { events_ |= kWriteEvent; update(); }
	void disableWriting() { events_ &= ~kWriteEvent; update(); }

	void disableAll() { events_ = kNoneEvent; update(); }

	bool isWriting() { return events_ & kWriteEvent; }
	bool isReading() { return events_ & kReadEvent; }
	bool isNoneEvent() { return events_ == kNoneEvent; }

	inline int fd() { return fd_; }
	inline int index() { return index_; }
	inline void set_index(int index) { index_ = index; }

private:

	static const int kNoneEvent;
	static const int kReadEvent;
	static const int kWriteEvent;

	void update();
	void handleEventWithGuard();

	EventLoop* loop_;
	const int  fd_;
	int 	   events_;
	int        revents_;
	int 	   index_;

	boost::weak_ptr<void> tie_;
	bool tied_;

	bool eventHandling_;
	bool addedToLoop_;

	EventCallBack writeCallback_;
	EventCallBack closeCallback_;
	EventCallBack readCallback_;
};


#endif /* CHANNEL_H_H */
