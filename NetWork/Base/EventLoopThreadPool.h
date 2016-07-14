#ifndef EVENT_LOOP_THREAD_POOL_H
#define EVENT_LOOP_THREAD_POOL_H
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/ptr_vector.hpp>

#include <string>

class EventLoop;
class EventLoopThreadPool : boost::noncopyable
{
public
	typedef boost::function<void(EventLoop*)> ThreadInitCallback;

	EventLoopThreadPool(EventLoop* baseLoop, const std::string& name);
	~EventLoopThreadPool();

	void setThreadNum(int numThreads)
	{ numThreads_ = numThreads; }

	void start(const ThreadInitCallback& cb = ThreadInitCallback());

	EventLoop* getNextLoop();

	EventLoop* getLoopForHash(size_t hashCode);

	std::vector<EventLoop*> getAllLoops();

	bool started() const
	{ return started_; }

	const std::string& name() const
	{ return name_; }

private:
	EventLoop* baseLoop_;
	std::string name_;
	bool started_;
	int numThreads_;
	int next_;
	boost::ptr_vector<EventLoopThread> threads_;
	std::vector<EventLoop*> loops_;
};












#endif /* EVENT_LOOP_THREAD_POOL_H */
