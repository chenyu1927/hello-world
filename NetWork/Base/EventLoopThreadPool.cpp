#include "EventLoopThreadPool.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop, const std::string& name)
	: baseLoop_(baseLoop),
	  name_(name),
	  started_(false),
	  numThreads_(0),
	  next_(0)
{

}

void EventLoopThreadPool::start(const ThreadInitCallback& cb)
{
	assert(!started_);

	started_ = true;
	for (int i = 0; i < numThreads_; ++ i)
	{
		char buf[name_.size() + 32];
		snprintf(buf, sizeof buf, "%s%d", name_.c_str(), i);
		EventLoopThread* t = new EventLoopThread(cd, buf);
		threads_.push_back(t);
		loops_.push_back(t->startLoop());
	}

	if (numThreads_ == 0 && cb)
	{
		cb(baseLoop);
	}
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
	assert(started_);
	EventLoop* loop = baseLoop_;

	if (!loops_.empty())
	{
		loop = loops_[next_];
		++ next_;
		if (implicit_cast<size_t>(next_) >= loops_.size())
		{
			next_ = 0;
		}
	}

	return loop;
}

EventLoop* EventLoopThreadPool::getLoopForHash(int hashCode)
{
	EventLoop* loop = baseLoop_;
	if (!loops_.empty())
	{
		loop = loops_[hashCode % loops_.size()];
	}

	return loop;
}

std::vector<EventLoop*> EventLoopThreadPool::getAllLoop()
{
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
