#ifndef EVENT_LOOP_H_H
#define EVENT_LOOP_H_H

#include <boost/noncopyable.hpp>
#include <memory>
#include "MutexLock.h"
#include "Timestamp.h"
#include <functional>
#include "TimerId.h"
//#include "Channel.h"
//#include "Epoller.h"

class Channel;
class Epoller;
class TimerQueue;

class EventLoop : boost::noncopyable
{
public:
	typedef std::function<void()> Functor;
	typedef std::function<void()> TimerCallback;

	EventLoop();
	~EventLoop();

	void loop();

	void quit();

	TimerId runAt(const Timestamp& time, TimerCallback&& cb);
	TimerId runAfter(double relay, TimerCallback&& cb);
	TimerId runEvery(double interval, TimerCallback&& cb);

	Timestamp pollReturnTime() const { return pollReturnTime_; }
	int64_t iteration() const { return iteration_; }

	void runInLoop(Functor&& cb);
	void queueInLoop(Functor&& cb);

	void wakeup();
	void updateChannel(Channel* channel);
	void removeChannel(Channel* channel);
	bool hasChannel(Channel* channel);

	void assertInLoopThread()
	{
		if (!isInLoopThread())
		{
			abortNotInLoopThread();
		}
	}

	bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }
	
	bool eventHandling() const { return eventHandling_; }

	static EventLoop* getEventLoopOfCurrentThread();

private:
	void abortNotInLoopThread();
	void handleRead();
	void doPendingFunctors();

	typedef std::vector<Channel*> ChannelVec;

	bool looping_;
	bool quit_;
	bool eventHandling_;
	bool callingPendingFunctors_;

	int64_t iteration_;
	const pid_t threadId_;
	Timestamp pollReturnTime_;

	std::unique_ptr<Epoller> epoller_;
	std::unique_ptr<TimerQueue> timerQueue_;

	int wakeupFd_;
	std::unique_ptr<Channel> wakeupChannel_;

	ChannelVec activeChannels_;
	Channel* currentActiveChannel_;

	MutexLock mutex_;
	std::vector<Functor> pendingFunctors_;
};




#endif /* EVENT_LOOP_H_H */
