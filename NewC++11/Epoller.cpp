#include "Epoller.h"
#include <sys/epoll.h>

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
	int n = ::epoll_wait(efd_, event_list_.begin(), 
			static_cast<int>(event_list_.size()), timeoutMs);

	int err = errno;
	Timestamp now(Timestamp::gettimeofday());
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
		fprintf(stderr, "nothing happen !");
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

void Epoller::fillActiveChannel(int numEvents, ChannelVec* activeChannels) const
{
	for (int i = 0; i < numEvents; ++ i)
	{
		Channel* pChannel = static_cast<Channel*>(event_list_[i].ptr);
		if (pChannel)
		{
//			update(event_list_[i].events, pChannel);
			int fd = pChannel->fd();
			auto iter = channel_map_.find(fd);
			assert(iter != channel_map_.end());

			pChannel->set_revents(event_list_[i].events);
			activeChannels.push_back(pChannel);
		}
	}
}
