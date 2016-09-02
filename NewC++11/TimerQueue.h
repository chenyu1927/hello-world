#ifndef TIMER_QUEUE_H_H
#define TIMER_QUEUE_H_H

#include <boost/noncopyable.hpp>
#include <set>
//#include <functional>
#include <memory>
#include "Channel.h"


class Timer;
class EventLoop;
class TimerId;

class TimerQueue : boost::noncopyable
{
public:

	typedef std::function<void()> TimerCallback;

	TimerQueue(EventLoop* loop);
	~TimerQueue();

	TimerId addTimer(TimerCallback&& cb, Timestamp when, double interval);

	void cancleTimer(TimerId timerId);

private:
	typedef std::pair<Timestamp, Timer*> Entry;
	typedef std::set<Entry> TimerList;
	typedef std::pair<Timer*, int64_t> ActiveTimer;
	typedef std::set<ActiveTimer> ActiveTimerSet;

	void addTimerInLoop(Timer* timer);
	void cancleTimerInLoop(TimerId timerId);

	std::vector<Entry> getEntry(Timestamp now);
	void reset(std::vector<Entry> expired, Timestamp now);
	void handleRead();

	bool insert(Timer* timer);


	EventLoop* loop_;
	const int timerfd_;
	Channel timerfdChannel_;
	TimerList timers_;

	ActiveTimerSet activeTimers_;
	bool callingExpiredTimers_;
	ActiveTimerSet cancleTimers_;
};






























#endif //TIMER_QUEUE_H_H
