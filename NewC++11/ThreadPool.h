#ifndef THREAD_POOL_H_H
#define THREAD_POOL_H_H

#include <boost/noncopyable.hpp>
#include <vector>
#include <deque>
#include <memory>
#include "Condition.h"

class Thread;

class ThreadPool : boost::noncopyable
{
public:
	typedef std::function<void()> Task;

	ThreadPool()
		:running_(false), mutex_(), empty_(mutex_), full_(mutex_),
		 maxQueueSize_(0)
	{
		
	}

	~ThreadPool();

	void setMaxQueueSize(int size) { maxQueueSize_ = size; }
	inline bool isFull();
	int queueSize();

	void runInThread();

	void start(int);
	void stop();

	void addTask(Task&& task);

private:
	Task _take();

	bool running_;
	MutexLock mutex_;
	Condition empty_;
	Condition full_;
	int maxQueueSize_;
//	std::vector<Thread*> threads_; //leak lost
	std::vector<std::shared_ptr<Thread>> threads_;
	std::deque<Task> tasks_list_;
};






#endif /* THREAD_POOL_H_H */
