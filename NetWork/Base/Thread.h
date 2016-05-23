#ifndef THREAD_H_H
#define THREAD_H_H
#include <pthread.h>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
//#include <boost/shared_ptr.hpp>
#include <string>
#include <sys/syscall.h>
//#include <unistd.h>


static pid_t gettid(void)
{
	return ::syscall(SYS_gettid);
}

class Thread : boost::noncopyable
{
public:
	typedef boost::function<void (void)> Func;
	explicit Thread(const Func& func, const std::string& name=std::string());
	~Thread();

	static void* runInThread(void *argv);

	void startFunc(void);
	void start();
	int join();

private:
	bool started_;
	bool joined_;
	std::string name_;
	pthread_t	id_;
	pid_t 		tid_;
//	boost::shared_ptr<pid_t> tid_;
	Func		func_;
};


#endif /* THREAD_H_H */
