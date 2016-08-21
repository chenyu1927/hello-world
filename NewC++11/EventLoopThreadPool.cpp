#include "EventLoopThreadPool.h"
#include "EventLoopThread.h"
#include "EventLoop.h"
#include <algorithm>
#include <sstream>
#include <assert.h>
#include "Type.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop, const std::string& name)
	: baseLoop_(baseLoop), name_(name), started_(false), numThreads_(0),
	  next_(0)
{

}

EventLoopThreadPool::~EventLoopThreadPool()
{
	// EventLoopThread is safe
/*	if (baseLoop_)
		baseLoop_->quit();
	std::for_each(loops_.begin(), loops_.end(), [] (EventLoop* loop) { loop->quit(); });*/
}

void EventLoopThreadPool::start(const ThreadInitCallback& cb)
{
	baseLoop_->assertInLoopThread(); // baseLoop_ must run in this thread;
	assert(!started_);
	started_ = true;

	for (int i = 0; i < numThreads_; ++ i)
	{
//		char buf[name_.size() + 32] = {0};
//		snprintf(buf, sizeof buf, "%s%d", name_.c_str(), i);
		std::stringstream ss;
		ss << name_ << i;
		std::shared_ptr<EventLoopThread> thread = std::make_shared<EventLoopThread>(cb, ss.str());
		threads_.push_back(thread);
		loops_.push_back(threads_[i]->startLoop());
	}

	if (numThreads_ == 0 && cb)
	{
		cb(baseLoop_);
	}
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
	assert(started_);
	baseLoop_->assertInLoopThread();

	EventLoop* loop = baseLoop_;
	if (!loops_.empty())
	{
		loop = loops_[next_];
		++ next_;
		if (implicit_cast<size_t>(next_) > loops_.size())
		{
			next_ = 0;
		}
	}

	return loop;
}

EventLoop* EventLoopThreadPool::getLoopForHash(size_t hashCode)
{
	baseLoop_->assertInLoopThread();
	EventLoop* loop = baseLoop_;

	if (!loops_.empty())
	{
		loop = loops_[hashCode % loops_.size()];
	}

	return loop;
}

std::vector<EventLoop*> EventLoopThreadPool::getAllLoops()
{
	baseLoop_->assertInLoopThread();
	assert(started_);
	
	if (loops_.empty())
	{
		return std::vector<EventLoop*>(1, baseLoop_);
	}
	else
	{
		return loops_;
	}
}
