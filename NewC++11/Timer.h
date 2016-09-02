#ifndef TIMER_H_H
#define TIMER_H_H

#include <boost/noncopyable.hpp>
#include <atomic>
#include <functional>
#include <utility> //move
#include "Timestamp.h"

class Timer : boost::noncopyable
{
public:
	typedef std::function<void()> TimerCallback;

	Timer(TimerCallback&& cb, Timestamp when, double interval)
		: callback_(std::move(cb)),
		  expiration_(when),
		  interval_(interval),
		  repeat_(interval_ > 0),
//		  s_numCreated_(0),
		  sequeue_(++ s_numCreated_)
	{

	}
	
	void run() const
	{
		callback_();
	}

	Timestamp expiration() const { return expiration_; }
	bool repeat() const { return repeat_; }
	int64_t sequeue() const { return sequeue_; }
	static int64_t numCreated() { return s_numCreated_.load(); }
	
	void restart(Timestamp now);

private:

	const TimerCallback callback_;
	Timestamp expiration_;
	const double interval_;
	const bool repeat_;
//	const int64_t sequeue_;
	static std::atomic<int64_t> s_numCreated_;
	const int64_t sequeue_;
};







#endif //TIMER_H_H
