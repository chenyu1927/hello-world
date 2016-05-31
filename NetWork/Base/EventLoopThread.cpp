#include "EventLoopThread.h"
#include <boost/bind.hpp>
#include "EventLoop.h"

EventLoopThread::EventLoopThread(const ThreadInitCallBack& cb, const std::string& name)
	: thread_(boost::bind(&EventLoopThread::threadFunc, this), name),
	  loop_(0),
	  exiting_(false),
	  mutex_(),
	  cond_(mutex_),
	  callback_(cb)
{

}

EventLoopThread::~EventLoopThread()
{
	exiting_ = true;
	if (loop_ != 0)
	{
		loop_->quit();
		thread_.join();
	}

}

void EventLoopThread::threadFunc()
{
	EventLoop loop;

	if (callback_)
	{
		callback_(&loop);
	}

	{
		MUTEX_GUARD(obj, mutex_);
		loop_ = &loop;
		cond_.notify();
	}

	loop.loop();
	loop_ = 0;
}

EventLoop* EventLoopThread::startLoop()
{
	assert(!thread_.started());
	thread_.start();

	{
		MUTEX_GUARD(obj, mutex_);
		while (loop_ == 0)
			cond_.wait();
	}

	return loop_;
}
