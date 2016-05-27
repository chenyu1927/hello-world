#include "Poll.h"
#include "Epoller.h"

Poller* Poller::newDefaultPoller(EventLoop *loop)
{
	return new EpollPoller(loop);
}
