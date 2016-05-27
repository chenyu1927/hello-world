#ifndef EVENT_LOOP_H_H
#define EVENT_LOOP_H_H

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>

#include "MutexLock.hpp"
//#include "Channel.h"
//#include "Poll.h"
class Channel;
class Poller;

class EventLoop : boost::noncopyable
{
public:
	typedef boost::function<void()> Functor;

	EventLoop();
	~EventLoop();

	void loop();

	void quit();
	
	void runInLoop(const Functor& cd);

	void queueInLoop(const Functor& cd);

	void wakeup();
	void updateChannel(Channel* channel);
	void removeChannel(Channel* channel);
	bool hasChannel(Channel* channel);
	
private:
	void handleRead();
	typedef std::vector<Channel*> ChannelList;


	bool looping_;
	bool quit_;
	bool eventHandling_;
	
	int wakeupFd_;
	boost::scoped_ptr<Channel> wakeupChannel_;
	boost::scoped_ptr<Poller> poller_;

	ChannelList activeChannels_;
	Channel*	currentActiveChannel_;

	MutexLock mutex_;

};

#endif /* EVENT_LOOP_H_H */
