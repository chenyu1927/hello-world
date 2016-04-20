#ifndef MUTEX_LOCK_H_H
#define MUTEX_LOCK_H_H

#include<pthread.h>
#include<boost/noncopyable.hpp>

class MutexLock
{
public:
	MutexLock(){
		::pthread_mutex_init(&mutex_, NULL);
	}

	~MutexLock(){
		::pthread_mutex_destroy(&mutex_);
	}

	int lock(){
		return ::pthread_mutex_lock(&mutex_);
	}

	int unlock(){
		return ::pthread_mutex_unlock(&mutex_);
	}
	
	pthread_mutex_t* getMutexLock()
	{
		return &mutex_;
	}

private:
	pthread_mutex_t mutex_;
};

class MutexGuard : boost::noncopyable
{
public:
	MutexGuard(MutexLock& mutex)
		: lock_(mutex)
	{
		lock_.lock();
	}

	~MutexGuard(){
		lock_.unlock();
	}

	MutexLock& getMutexLock(){
		return lock_;
	}

private:
	MutexLock& lock_;
};

#define MUTEX_GUARD(OBJ, LOCK) MutexGuard OBJ(LOCK)

#endif /* MUTEX_LOCK_H_H */
