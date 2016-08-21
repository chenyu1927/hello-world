#ifndef EVENT_LOOP_THREAD_H_H
#define EVENT_LOOP_THREAD_H_H

#include <boost/noncopyable.hpp>
#include "Thread.h"
#include "MutexLock.h"
#include "Condition.h"
#include <string>

class EventLoop;

class EventLoopThread : boost::noncopyable
{
public:
	typedef std::function<void (EventLoop*)> ThreadInitCallback;
	
	EventLoopThread(const ThreadInitCallback& cb = ThreadInitCallback(),  
			const std::string& name = std::string());
	~EventLoopThread();

	EventLoop* startLoop();

private:
	void threadFunc();
	
	EventLoop* loop_;
	bool exiting_;
	Thread thread_;
	MutexLock mutex_;
	Condition cond_;
	ThreadInitCallback callback_;
};



#endif /* EVENT_LOOP_THREAD_H_H */
