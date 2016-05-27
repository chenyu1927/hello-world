#include "Epoller.h"
#include "Poll.h"
#include "Channel.h"
#include <assert.h>
#include <sys/epoll.h>
#include "type.h"
#include <errno.h>

namespace
{
const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;
}


EpollPoller::EpollPoller(EventLoop* loop)
	: Poller(loop),
	  efd_(::epoll_create1(EPOLL_CLOEXEC)),
	  events_(kInitEventListSize)
{
	if (efd_ < 0)
	{
		//log
		abort();
	}
}

EpollPoller::~EpollPoller()
{
	::close(efd_);
}

void EpollPoller::updateChannel(Channel* channel)
{
	const int index = channel->index();
	if (index == kNew || index == kDeleted)
	{
		int fd = channel->fd();
		if (index == kNew)
		{
			assert(channels_.find(fd) == channels_.end());
			channels_[fd] = channel;
		}
		else
		{
			assert(channels_.find(fd) != channels_.end());
			assert(channels_[fd] == channel);
		}

		channel->set_index(kAdded);
		update(EPOLL_CTL_ADD, channel);
	}
	else
	{
		int fd = channel->fd();
		assert(channels_.find(fd) != channels_.end());
		assert(channels_[fd] == channel);
		assert(index == kAdded);

		if (channel->isNoneEvent())
		{
			update(EPOLL_CTL_DEL, channel);
			channel->set_index(kDeleted);
		}
		else
		{
			update(EPOLL_CTL_MOD, channel);
		}
	}
}

void EpollPoller::removeChannel(Channel* channel)
{
	int fd = channel->fd();
	assert(channels_.find(fd) != channels_.end());
	assert(channels_[fd] == channel);
	assert(channel->isNoneEvent());
	int index = channel->index();
	assert(index == kAdded || index == kDeleted);
	size_t n = channels_.erase(fd);
	(void)n;
	assert(n == 1);

	if (index == kAdded)
	{
		update(EPOLL_CTL_DEL, channel);
	}
	channel->set_index(kNew);
}

void EpollPoller::update(int operation, Channel* channel)
{
	struct epoll_event ev;
	bzero(&ev, sizeof ev);
	ev.events = channel->getEvents();
	ev.data.ptr = channel;
	int fd = channel->fd();
	if (::epoll_ctl(efd_, operation, fd, &ev) < 0)
	{
		if (operation == EPOLL_CTL_DEL)
		{
			//FIXME::log
			//
		}
		else
		{

		}
	}
}


Timestamp EpollPoller::poll(int timeoutMs, ChannelList& activeChannels)
{
	int numEvents = ::epoll_wait(efd_, 
								 &*events_.begin(), 
								 static_cast<int>(events_.size()), 
								 timeoutMs);
	int saveErrno = errno;
	Timestamp now(Timestamp::now());
	if (numEvents > 0)
	{
		fillActiveChannels(numEvents, activeChannels);
		if (implicit_cast<size_t>(numEvents) == events_.size())
		{
			events_.resize(events_.size() * 2);
		}
	}
	else if (numEvents == 0)
	{
		
	}
	else
	{
		if (saveErrno != EINTR)
		{
			//log
		}
	}

	return now;
}

void EpollPoller::fillActiveChannels(int numEvents, 
									 ChannelList& activeChannels) const
{
	assert(implicit_cast<size_t>(numEvents) <= events_.size());
	for (int i = 0; i < numEvents; ++ i)
	{
		Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
		channel->setRevents(events_[i].events);
		activeChannels.push_back(channel);
	}
}


