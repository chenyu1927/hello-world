#include "Thread.h"
#include <boost/static_assert.hpp>
#include <stdlib.h>

Thread::Thread(const Func& func, const std::string& name)
	: started_(false),
	  joined_(false),
	  name_(name),
	  id_(0),
	  tid_(0),
	  func_(func)
{

}


void* Thread::runInThread(void *argv)
{
	Thread *self = static_cast<Thread *>(argv);
	assert(!self->func_.empty()); //如果为空，调用会抛出异常
	
	self->startFunc();
	return self;
}

void Thread::startFunc()
{
	assert(!func_.empty());
	tid_ = gettid();
	try
	{
		func_();
	}
	catch (...)
	{
		/*FIXME:log */
		::abort();
		//....
	}
}

void Thread::start()
{
	assert(started_ == false);
	if (::pthread_create(&id_, NULL, runInThread, this) != 0)
	{
		
	}
	else
	{
		started_ = true;
	}
}

int Thread::join()
{
	assert(started_);
	assert(joined_ == false);
	joined_ = true;
	return ::pthread_join(id_, NULL);
}

Thread::~Thread()
{
	if (started_ && !joined_)
		::pthread_detach(id_);
	// 将线程设置成unjoined状态， 这样程序退出会回收资源
}
