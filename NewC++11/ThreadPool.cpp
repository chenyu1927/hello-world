#include "ThreadPool.h"
#include "Thread.h"
#include <algorithm>

void ThreadPool::start(int threadsNum)
{
	assert(threads_.empty());
	running_ = true; //标识线程池启动
	for (auto i = 0; i < threadsNum; ++ i)
	{
		std::shared_ptr<Thread> thread = 
			std::make_shared<Thread>(std::bind(&ThreadPool::runInThread, this));
//		thread->start();
		threads_.push_back(thread);
		threads_[i]->start();
	}
}

void ThreadPool::runInThread()
{
//	assert(!running_);
//	running_ = true;
	while (running_)
	{
		Task task(_take());  //这里的抽象很重要
		if (task)
			task();
	}
}

int ThreadPool::queueSize()
{
	MUTEX_GUARD(mutex_, Obj);
	return tasks_list_.size();
}

bool ThreadPool::isFull()
{
	mutex_.assertLocked();
	return maxQueueSize_ > 0 && 
		tasks_list_.size() >= maxQueueSize_;
}

ThreadPool::Task ThreadPool::_take() 
{
	MUTEX_GUARD(mutex_, Obj);
	while (tasks_list_.empty() && running_)
		empty_.wait();
//	assert(!tasks_list_.empty());
	Task task;
	if (!tasks_list_.empty())
	{
		task = tasks_list_.front();
		tasks_list_.pop_front();
		if (maxQueueSize_ > 0)
			full_.notify();
	}
	return task;
}

void ThreadPool::addTask(Task&& task)
{
	if (threads_.empty())
	{
		task();
	}
	else
	{
		MUTEX_GUARD(mutex_, Obj);
		while (isFull())
			full_.wait();

		tasks_list_.push_back(task);
		empty_.notifyAll();
	}
}

ThreadPool::~ThreadPool()
{
	if (running_)
	{
/*		running_ = false;
		empty_.notifyAll();
		std::for_each(threads_.begin(), threads_.end(),
				[] (Thread* thread) { thread->join(); });
		*/
		stop();
	}
}

void ThreadPool::stop()
{
	{
		MUTEX_GUARD(mutex_, Obj);
		assert(running_);
		running_ = false;
		empty_.notifyAll();
	}

	std::for_each(threads_.begin(), threads_.end(), 
			[](std::shared_ptr<Thread>& thread) { thread->join(); });

}
