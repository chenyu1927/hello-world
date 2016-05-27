#ifndef POLL_H_H
#define POLL_H_H
#include <map>
#include <vector>
#include <boost/noncopyable.hpp>
#include "Timestamp.h"
class Channel;
class EventLoop;

class Poller : boost::noncopyable
{
public:
	typedef std::vector<Channel*> ChannelList;

	Poller(EventLoop* loop);
	virtual ~Poller();

	virtual void updateChannel(Channel* channel) = 0;

	virtual void removeChannel(Channel* channel) = 0;

	virtual bool hasChannel(Channel* channel);

	virtual Timestamp poll(int timeoutMs , ChannelList& activeChannels) = 0;

	static Poller* newDefaultPoller(EventLoop* loop);

protected:
	typedef std::map<int, Channel*> ChannelMap;
	ChannelMap channels_;

private:
	EventLoop* ownerLoop_;
};


#endif /*POLL_H_H  */
