#ifndef THREAD_H_H
#define THREAD_H_H

#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <functional>
#include <string>
#include <utility>
#include <memory>

class Thread : boost::noncopyable
{
//	using std::string;
public:
	typedef std::function<void ()> ThreadFunc;

	explicit Thread(const ThreadFunc& func, const std::string& name = std::string())
		: start_(false), join_(false),
		  pid_(0), tid_(new pid_t(0)),
		  func_(func), name_(name)
	{
		_setDefaultName();
	}

	explicit Thread(ThreadFunc&& func, const std::string& name = std::string())
		: start_(false), join_(false),
		  pid_(0), tid_(new pid_t(0)),
		  func_(std::move(func)), name_(name)
	{
		_setDefaultName();
	}

	~Thread();

	bool started() { return start_; }
	bool joined() { return join_; }

	void start();
	void join();

	const std::string& name() const { return name_; }
	pid_t tid() const { return *tid_; }

private:
	void _setDefaultName();

	bool 	    start_;
	bool 	    join_;
	pthread_t   pid_;
	std::shared_ptr<pid_t> tid_; //这里用智能指针不是很理解: 明白了，这是为了在ThreadData中可以改变它
	ThreadFunc 	func_;
	std::string name_;

	static int num_;  //
};



#endif /*THREAD_H_H */
