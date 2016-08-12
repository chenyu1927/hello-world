#ifndef MUTEX_LOCK_H_H
#define MUTEX_LOCK_H_H

#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <assert.h>
#include "CurrentThread.h"

//如何确定哪个线程上的锁，由哪个线程解锁
class MutexLock : boost::noncopyable //这中资源不可以复制的
{
	friend class Condition;
public:
	MutexLock()
		: holder_(0)
	{
		::pthread_mutex_init(&mutex_, 0);
	}

	~MutexLock()
	{
		assert(holder_ == 0);
		::pthread_mutex_destroy(&mutex_);
	}

	void lock()
	{
		::pthread_mutex_lock(&mutex_);
		assignHolder();   // 只有上了锁才能赋值
	}

	int unlock()
	{
		unassignHolder();
		return ::pthread_mutex_unlock(&mutex_);
	}

	bool isLockedByThisThread() const
	{
		return holder_ == CurrentThread::tid();
	}

	void assertLocked() const
	{
		assert(isLockedByThisThread());
	}

	pthread_mutex_t* getMutex()
	{
		return &mutex_;
	}

private:
	class UnassignHolder : boost::noncopyable
	{
	public:
		UnassignHolder(MutexLock& owner)
			:owner_(owner)
		{
			owner_.unassignHolder();
		}
		
		~UnassignHolder()
		{
			owner_.assignHolder();
		}
	private:
		MutexLock& owner_;
	};

private:
	void unassignHolder()
	{
		holder_ = 0;
	}

	void assignHolder()
	{
		holder_ = CurrentThread::tid();
	}


	pthread_mutex_t mutex_;
	pid_t holder_;    //保存上锁的线程
};


class MutexLockGuard : boost::noncopyable
{
public:
	explicit MutexLockGuard(MutexLock& mutex)
		: mutex_(mutex)
	{
		mutex_.lock();
	}

	~MutexLockGuard()
	{
		mutex_.unlock();
	}

private:
	MutexLock& mutex_;
};


#define MUTEX_GUARD(m, obj) MutexLockGuard obj(m)







#endif /* MUTEX_H_H */
