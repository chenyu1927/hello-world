#ifndef EVENTLOOPTHREADPOOL_H_H
#define EVENTLOOPTHREADPOOL_H_H

#include <boost/noncopyable.hpp>
#include <string>
#include <vector>
#include <functional>
#include <memory>

class EventLoop;
class EventLoopThread;

class EventLoopThreadPool : boost::noncopyable
{
public:
	typedef std::function<void(EventLoop*)> ThreadInitCallback;

	EventLoopThreadPool(EventLoop* baseLoop, const std::string& name = std::string());
	~EventLoopThreadPool();

	void setNumThreads(const int num) { numThreads_ = num; }
	void start(const ThreadInitCallback& cb = ThreadInitCallback());

	EventLoop* getNextLoop();

	EventLoop* getLoopForHash(size_t hashCode);
	std::vector<EventLoop*> getAllLoops();

	bool started() const { return started_; }
	const std::string& name() const { return name_; }

private:
	EventLoop* baseLoop_;
	std::string name_;
	bool started_;
	int numThreads_;
	int next_;
	
	std::vector<std::shared_ptr<EventLoopThread>> threads_;
	std::vector<EventLoop*> loops_;
};











#endif /* EVENTLOOPTHREADPOOL_H_H */
