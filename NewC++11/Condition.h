#ifndef CONDITION_H_H
#define CONDITION_H_H

#include "MutexLock.h"

class Condition : boost::noncopyable
{
public:
	Condition(MutexLock& mutex)
		: mutex_(mutex)
	{
		::pthread_cond_init(&cond_, 0);
	}

	~Condition()
	{
		::pthread_cond_destroy(&cond_);
	}

	int wait()
	{
//		MutexLock::unassignHolder();
		MutexLock::UnassignHolder uh(mutex_);
		return ::pthread_cond_wait(&cond_, mutex_.getMutex());
	}

	void notify()
	{
		::pthread_cond_signal(&cond_);
	}

	void notifyAll()
	{
		::pthread_cond_broadcast(&cond_);
	}

private:
	MutexLock& mutex_;
	pthread_cond_t cond_;
};




#endif /* CONDITION_H_H */
