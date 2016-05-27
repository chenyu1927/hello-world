#include "Poll.h"
#include "Channel.h"
Poller::Poller(EventLoop* loop)
	: ownerLoop_(loop)
{

}

Poller::~Poller()
{

}

bool Poller::hasChannel(Channel* channel)
{
	ChannelMap::const_iterator iter = channels_.find(channel->fd());
	return iter != channels_.end();
}


