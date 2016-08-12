#include "Thread.h"
#include "CurrentThread.h"
#include <assert.h>
#include <type_traits> //is_same
#include <unistd.h>
#include <sys/prctl.h>
#include <stdio.h>
#include <sys/syscall.h>

namespace CurrentThread
{//个人理解是为了更快的访问
	__thread int t_cacheTid = 0; //每个thread单独拥有 __thread
	__thread const char* t_threadName = "unknown";

	const bool sameType = std::is_same<int, pid_t>::value;
	static_assert(sameType, "pid_t not eq int");
}

namespace detail
{
	pid_t gettid()
	{
		return static_cast<pid_t>(::syscall(SYS_gettid));
	}
}

struct ThreadData
{
//	using std::string;
	typedef Thread::ThreadFunc ThreadFunc;
	ThreadFunc func_;
	std::string name_;
	std::weak_ptr<pid_t> wkTid_;

	ThreadData(const ThreadFunc& func, const std::string& name, 
			const std::shared_ptr<pid_t>& tid)
		: func_(func), name_(name), wkTid_(tid)
	{
		
	}

	void runInThread()
	{
		pid_t tid = CurrentThread::tid();
		std::shared_ptr<pid_t> ptid = wkTid_.lock();
		if (ptid)
		{
			*ptid = tid;
			ptid.reset();
		}

		CurrentThread::t_threadName = name_.empty() ? "chenyuThread" : name_.c_str();
		::prctl(PR_SET_NAME, CurrentThread::t_threadName);
		try
		{
			func_(); //可能抛出异常
			CurrentThread::t_threadName = "finished";
		}
		catch (std::exception& ex)
		{
			CurrentThread::t_threadName = "crashed";
			fprintf(stderr, "exception caught in thread %s\n", name_.c_str());
			fprintf(stderr, "reason: %s\n", ex.what());
			abort();
		}
		catch (...)
		{
			CurrentThread::t_threadName = "crashed";
			fprintf(stderr, "exception caught in thread %s\n", name_.c_str());
			throw ;
		}
	}


};

void CurrentThread::cacheTid()
{
	if (t_cacheTid == 0)
	{
		t_cacheTid = detail::gettid();
	}
}

bool CurrentThread::isMainThread()
{
	return tid() == getpid();
}

void CurrentThread::sleepUsec(int64_t usec)
{
	
}

void* startThread(void* argv)
{
	ThreadData* t_data = static_cast<ThreadData*>(argv);
	assert(t_data);
	t_data->runInThread();
	delete t_data;
	return nullptr;
}

void afterFork()
{
	CurrentThread::t_cacheTid = 0;
	CurrentThread::t_threadName = "main";
	CurrentThread::tid();
}

class MainThreadNameInit
{
public:
	MainThreadNameInit()
	{
		CurrentThread::t_threadName = "main";
		CurrentThread::tid();
		pthread_atfork(0, 0, afterFork);
	}
};

MainThreadNameInit mainThreadName;


int Thread::num_ = 0;

void Thread::start()
{
	assert(!start_);
	start_ = true;

	ThreadData* t_data = new ThreadData(std::move(func_), name_, tid_);
	if (::pthread_create(&pid_, 0, startThread, t_data) != 0)
	{
		//log
		start_ = false;
		delete t_data;
	}
//	start_ = true;
}

void Thread::join()
{
	if (start_)
	{
		assert(!join_);
	    join_ = true;
		::pthread_join(pid_, 0);
	}
}

Thread::~Thread()
{
	if (start_ && !join_)
	{
		::pthread_detach(pid_);
	}
}

void Thread::_setDefaultName()
{
	int num  = __sync_add_and_fetch(&num_, 1);
	if (name_.empty())
	{
		char buff[32];
		snprintf(buff, sizeof buff, "Thread %d", num);
		name_ = buff;
	}
}

