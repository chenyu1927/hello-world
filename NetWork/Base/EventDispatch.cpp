#include "EventDispatch.h"
#include <sys/epollfd.h>
#include <sys/epoll.h>
#include <stdlib.h>

EventDispatch::EventDispatch()
	: running_(false)
{
	efd_ = ::epoll_create(1024);
	// now 1024 is ignored
	if (efd < 0)
	{
		abort();
	}
}

int EventDispatch::AddEvent(socket_t sockfd, uint8_t event)
{
	epoll_event events;
	bzero(&events, sizeof (epoll_event));

	if (event & EVENT_READ)
	{
		events.events |= (EPOLLIN | EPOLLET);
	}

	if (event & EVENT_WRITE)
	{
		events.events |= (EPOLLOUT | EPOLLET);
	}

	events.data.fd = sockfd;
	if (::epoll_ctl(efd_, EPOLL_CTL_ADD, events.data.fd, &events) < 0)
	{
		return -1;
	}

	return 0;
}

int EventDispatch::RemoveEvent(socket_t sockfd, uint8_t event)
{
	if (::epoll_ctl(efd_, EPOLL_CTL_DEL, sockfd, NULL) < 0)
	{
		return -1;
	}

	return 0;
}

void EventDispatch::loop()
{
	if (running_)
		return ;

	running_ = true;
	epoll_event events[1024];
	int nfd;
	while (running_)
	{
		nfd = epoll_wait(efd_, events, 1024, -1);
		for (int i = 0; i < nfd; ++ i)
		{
			int ev_fd = events[i].data.fd;
			BaseSocket *psock = FindBaseSocket(ev_fd);

			if (psock == NULL)
				continue ;

			if (events[i].events & EPOLLIN)
				psock->OnRead();
			if (events[i].events & EPOLLOUT)
				psock->OnWrite();
			
		}
	}

}

void EventDispatch::quit()
{
	running_ = false;
}


