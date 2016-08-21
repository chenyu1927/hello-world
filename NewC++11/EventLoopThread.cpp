#include "EventLoopThread.h"
#include "EventLoop.h"

EventLoopThread::EventLoopThread(const ThreadInitCallback& cb,
		const std::string& name)
	: loop_(nullptr), exiting_(false), 
	  thread_(std::bind(&EventLoopThread::threadFunc, this), name),
	  mutex_(), cond_(mutex_), callback_(cb)
{

}

EventLoopThread::~EventLoopThread()
{
	exiting_ = true;
	if (loop_)
	{
		loop_->quit();
		thread_.join();
	}
}

EventLoop* EventLoopThread::startLoop()
{
	assert(!thread_.started());
	thread_.start();

	{
		MUTEX_GUARD(mutex_, Obj);
		while (!loop_)
			cond_.wait();
	}

	return loop_;
}

void EventLoopThread::threadFunc()
{
	EventLoop loop;

	if (callback_)
	{
		callback_(&loop);
	}
	
	{
		MUTEX_GUARD(mutex_, Obj);
		loop_ = &loop;
		cond_.notify();
	}

	loop_->loop();
	loop_ = nullptr;
}

