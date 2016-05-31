#ifndef EVENT_LOOP_THREAD_H_H
#define EVENT_LOOP_THREAD_H_H

//#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
//#include <string>

#include "Thread.h"
#include "MutexLock.hpp"
#include "Condition.hpp"


class EventLoop;

class EventLoopThread : boost::noncopyable
{
public:
	typedef boost::function<void(EventLoop *)> ThreadInitCallBack;

	EventLoopThread(const ThreadInitCallBack& cb = ThreadInitCallBack(), 
					const std::string& name = std::string());

	~EventLoopThread();

	EventLoop* startLoop();
private:
	void threadFunc();
	
	Thread thread_;
	EventLoop *loop_;
	bool exiting_;
	MutexLock mutex_;
	Condition cond_;

	ThreadInitCallBack callback_;
};


























#endif /* EVENT_LOOP_THREAD_H_H */
