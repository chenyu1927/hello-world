#ifndef TIMER_ID_H_H
#define TIMER_ID_H_H

class Timer;

class TimerId
{
public:
	TimerId()
		: timer_(nullptr),
		  sequeue_(0)
	{

	}

	TimerId(Timer* timer, int64_t seq)
		: timer_(timer),
		  sequeue_(seq)
	{

	}

	friend class TimerQueue;
private:
	Timer* timer_;
	int64_t sequeue_;
};









#endif //TIMER_ID_H_H
