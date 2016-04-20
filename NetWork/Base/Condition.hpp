#ifndef CONDITION_H_H
#define CONDITION_H_H

#include <pthread.h>
#include <boost/noncopyable.hpp>
#include "MutexLock.hpp"
class Condition : boost::noncopyable
{
public:
	Condition(MutexLock& mutex)
		: mutex_(mutex)
	{
		::pthread_cond_init(&cond_, NULL);
	}

	~Condition(){
		::pthread_cond_destroy(&cond_);
	}

	void wait(){
		::pthread_cond_wait(&cond_, mutex_.getMutexLock());
	}

	void notify(){
		::pthread_cond_signal(&cond_);
	}
	
	void notifyAll(){
		::pthread_cond_broadcast(&cond_);
	}

private:
	MutexLock&	   mutex_;
	pthread_cond_t cond_;
};


#endif /* CONDITION_H_H */
