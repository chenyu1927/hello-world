#ifndef BLOCK_QUEUE_H_H
#define BLOCK_QUEUE_H_H

#include <boost/noncopyable.hpp>
#include "MutexLock.hpp"
#include "Condition.hpp"
#include <deque>

template <typename T>
class BlockQueue : boost::noncopyable
{
public:
	BlockQueue();
//	~BlockQueue();

	void put(T& t);
	T take();
	size_t size();

private:
	MutexLock 	  mutex_;
	Condition	  cond_;
	std::deque<T> queue_;
};

template <typename T>
inline BlockQueue<T>::BlockQueue()
	: mutex_(),
	  cond_(mutex_)
{
	queue_.clear();   //no exception
}

template <typename T>
void BlockQueue<T>::put(T& t)
{
	MUTEX_GUARD(obj, mutex_);
	queue_.push_back(t); //strong exception guarantee
	cond_.notify();
}

template <typename T>
T BlockQueue<T>::take()
{
	MUTEX_GUARD(obj, mutex_);
	while (queue_.empty()) //no exception
		cond_.wait();
	T t = queue_.front();
	queue_.pop_front();  // do not throw

	return t;
}

template <typename T>
size_t BlockQueue<T>::size()
{
	MUTEX_GUARD(obj, mutex_);

	return queue_.size(); // no exception
}


#endif /* BLOCK_QUEUE_H_H */
