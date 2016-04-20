#ifndef THREAD_POOL_H_H
#define THREAD_POOL_H_H

#include <boost/noncopyable.hpp>
#include "Thread.h"
#include <queue>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/function.hpp>
#include "Condition.hpp"
#include "MutexLock.hpp"

class ThreadPool : boost::noncopyable
{
public:
	typedef boost::function<void ()> Task;

	explicit ThreadPool();
	~ThreadPool();
	
	void start(size_t threadNum=0);
	void stop();
	void addTask(Task func);
	Task takeTask();
	void setMaxQueueSize(size_t size);

private:
	void runInThread();
	bool isFull();

private:
	bool running_;
	size_t maxQueueSize_;
	MutexLock mutex_;
	Condition notEmpty_;
	Condition notFull_;

	boost::ptr_vector<Thread> threads_;
	std::deque<Task> tasks_;
};

#endif /* THREAD_POOL_H_H */
