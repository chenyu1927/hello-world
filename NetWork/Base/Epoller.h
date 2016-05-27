#ifndef EPOLLER_H_H
#define EPOLLER_H_H

#include "Poll.h"
#include <vector>

struct epoll_event;

class EpollPoller : public Poller
{
public:
	EpollPoller(EventLoop* loop);
	virtual ~EpollPoller();

	virtual void updateChannel(Channel* channel);
	virtual void removeChannel(Channel* channel);

	virtual Timestamp poll(int timeoutMs, ChannelList& activeChannels);
	
private:
	static const int kInitEventListSize = 16;

	void update(int operators, Channel* channel);
	void fillActiveChannels(int numEvents, ChannelList& activeChannels) const;

	typedef std::vector<struct epoll_event> EventList;

	int efd_;   // epoll fd
	EventList events_;
};




#endif /*EPOLLER_H_H */
