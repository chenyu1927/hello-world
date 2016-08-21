#ifndef EPOLLER_H_H
#define EPOLLER_H_H

#include <vector>
#include <map>
#include <boost/noncopyable.hpp>
#include "Timestamp.h"
#include "EventLoop.h"

class Channel;
//class EventLoop;

struct epoll_event;

class Epoller : boost::noncopyable
{
public:
	typedef std::vector<Channel*> ChannelVec;

	Epoller(EventLoop* loop);
	~Epoller();

	// return Timestamp and fill active channel
	Timestamp poll(int timeoutMs, ChannelVec* channelVec);

	void updateChannel(Channel* channel);

	void removeChannel(Channel* channel);

	bool hasChannel(Channel* channel) const;

	void assertInLoopThread() const
	{
		loop_->assertInLoopThread();
	}


private:

	static const int kInitEventVecSize = 16;

	static const char* operationToString(int op);

	void fillActiveChannels(int numEvents, ChannelVec* activeChannels) const;

	void update(int operation, Channel* channel);

	typedef std::map<int, Channel*> ChannelMap;
	typedef std::vector<struct epoll_event> EventVec;

	int efd_;   //epollfd
	EventLoop* loop_;  //
	EventVec event_list_;
	ChannelMap channel_map_;
};













#endif /* EPOLLER_H_H */
