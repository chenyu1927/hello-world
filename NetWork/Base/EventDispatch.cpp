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

int EventDispatch::addEvent(socket_t sockfd, uint8_t event)
{
	epoll_event events;
	bzero(&events, sizeof (epoll_event));

	if (event & EVENT_ALL)
	{
		events.events |= (EPOLLIN | EPOLLOUT | EPOLLET);
	}
	else if (event & EVENT_READ)
	{
		events.events |= (EPOLLIN | EPOLLET);
	}
	else if (event & EVENT_WRITE)
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

int EventDispatch::removeEvent(socket_t sockfd, uint8_t event)
{

}
