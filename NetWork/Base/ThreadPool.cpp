#include "ThreadPool.h"
#include <boost/bind.hpp>
ThreadPool::ThreadPool()
	: running_(false),
	  maxQueueSize_(0),
	  notEmpty_(mutex_),
	  notFull_(mutex_)
{

}

ThreadPool::~ThreadPool()
{
	if (running_)
		stop();
}

inline void ThreadPool::setMaxQueueSize(size_t size)
{
	maxQueueSize_ = size;
}

void ThreadPool::start(size_t threadNum)
{
//	assert(running_ == false);
	assert(threads_.empty());
	running_ = true;
	threads_.reserve(threadNum);
	for (size_t i = 0; i < threadNum; ++ i)
	{

/*		Thread *thread = new Thread(boost::bind(&ThreadPool::runInThread, this));
		thread->start();
		threads_.push_back(thread);*/ //bad
		//ptr_vector必须先push后对对象操作， 不然会有问题， 而且错误很难调试
		threads_.push_back(new Thread(boost::bind(&ThreadPool::runInThread, this)));
		threads_[i].start();
	}
}

bool ThreadPool::isFull()
{

	return maxQueueSize_ > 0 && tasks_.size() >= maxQueueSize_;
}

/*bool ThreadPool::isEmpty()
{
//	MUTEX_GUARD(obj, mutex_);
	return tasks_.empty();
}*/

void ThreadPool::runInThread()
{
	while (running_)
	{
		Task task(takeTask());
		if (task)
		{
			task();
		}
	}
}

void ThreadPool::addTask(Task func)
{
//	MUTEX_GUARD(obj, mutex_);
	if (threads_.empty())
	{
		func();
	}
	else
	{
		MUTEX_GUARD(obj, mutex_);
		while (isFull())
			notFull_.wait();
		assert(!isFull());
		tasks_.push_back(func);
		notEmpty_.notify();
	}
}

ThreadPool::Task ThreadPool::takeTask()
{
	MUTEX_GUARD(obj, mutex_);
	while (tasks_.empty() && running_)
		notEmpty_.wait();

	Task task;
	if (!tasks_.empty())
	{
		task = tasks_.front();
		tasks_.pop_front();
		if (maxQueueSize_ > 0)
			notFull_.notify();
	}
	return task;
}

void ThreadPool::stop()
{
	{
		MUTEX_GUARD(obj, mutex_);
		running_ = false;
		notEmpty_.notifyAll();
	}
	boost::ptr_vector<Thread>::iterator iter = threads_.begin();
	for (; iter != threads_.end(); ++ iter)
	{
		iter->join();
	}
/*	for_each(threads_.begin(),
			threads_.end(),
			boost::bind(&Thread::join, _1));*/
}
