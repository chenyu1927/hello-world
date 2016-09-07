#include "Epoller.h"
#include "Type.h"
#include "Channel.h"
#include "EventLoop.h"
#include <stdio.h>
#include <assert.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <strings.h>

namespace
{
	static const int kNew = -1;
	static const int kAdded = 1;
	static const int kDeleted = 2;
}

Epoller::Epoller(EventLoop* loop)
	: efd_(::epoll_create1(EPOLL_CLOEXEC)),
	  loop_(loop),
	  event_list_(kInitEventVecSize)
{
	if (efd_ < 0)
	{
		fprintf(stderr, "Epoller create error");
		abort();
	}
}

Epoller::~Epoller()
{
	::close(efd_);
}

Timestamp Epoller::poll(int timeoutMs, ChannelVec* channels)
{
	int n = ::epoll_wait(efd_, &(*event_list_.begin()), 
			static_cast<int>(event_list_.size()), timeoutMs);

	int err = errno;
	Timestamp now(Timestamp::now());
	if (n > 0)
	{
		channels->clear();
		fillActiveChannels(n, channels);
		if (implicit_cast<size_t>(n) == event_list_.size())
		{
			event_list_.resize(event_list_.size() * 2);
		}
	}
	else if (n == 0)
	{
		// nothing happen
//		fprintf(stderr, "nothing happen !");
	}
	else
	{
		if (err != EINTR) //信号中断
		{
			fprintf(stderr, "epoll wait error");
		}
	}

	return now;
}

void Epoller::fillActiveChannels(int numEvents, ChannelVec* activeChannels) const
{
	for (int i = 0; i < numEvents; ++ i)
	{
		Channel* pChannel = static_cast<Channel*>(event_list_[i].data.ptr);
		if (pChannel)
		{
//			update(event_list_[i].events, pChannel);
			int fd = pChannel->fd();
			auto iter = channel_map_.find(fd);
			assert(iter != channel_map_.end());

			pChannel->set_revents(event_list_[i].events);
			activeChannels->push_back(pChannel);
		}
	}
}

bool Epoller::hasChannel(Channel* channel) const
{
	const auto iter = channel_map_.find(channel->fd());
	return iter != channel_map_.end() && iter->second == channel;
}

void Epoller::updateChannel(Channel* channel)
{
	assertInLoopThread();
	const int index = channel->index();
	const int fd = channel->fd();
	if (index == kNew || index == kDeleted)
	{
		if (kNew == index)
		{
			assert(channel_map_.find(fd) == channel_map_.end());
			channel_map_[fd] = channel;
		}
		else 
		{
			assert(channel_map_.find(fd) != channel_map_.end());
			assert(channel_map_[fd] == channel);
		}

		channel->set_index(kAdded);
		update(EPOLL_CTL_ADD, channel);
	}
	else
	{
		assert(channel_map_.find(fd) != channel_map_.end());
		assert(channel_map_[fd] == channel);
	
		if (channel->isNoneEvent())
		{
			update(EPOLL_CTL_DEL, channel);
			channel->set_index(kDeleted);
		}
		else
			update(EPOLL_CTL_MOD, channel);
	}
}

void Epoller::removeChannel(Channel* channel)
{
	assertInLoopThread();
	int fd = channel->fd();
	assert(channel_map_.find(fd) != 
			channel_map_.end());
	assert(channel_map_[fd] == channel);
	assert(channel->isNoneEvent());

	int index = channel->index();
	assert(index == kAdded || index == kDeleted);
	size_t n = channel_map_.erase(fd);
	assert(n == 1);
	if (index == kAdded)
	{
		update(EPOLL_CTL_DEL, channel);
	}

	channel->set_index(kNew);
}

void Epoller::update(int operation, Channel* channel)
{
	struct epoll_event event;
	bzero(&event, sizeof event);
	event.events = channel->events();
	event.data.ptr = channel;

	int fd = channel->fd();
	if (::epoll_ctl(efd_, operation, fd, &event) < 0)
	{
		fprintf(stderr, "Epoller epoll_ctl() error");
	}
}


