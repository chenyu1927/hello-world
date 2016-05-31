#include "SocketsOpt.h"
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

int createNonblockingOrDie(sa_family_t family)
{
	int sockfd = ::socket(family, SOCK_STREAM | SOCK_CLOEXEC | SOCK_NONBLOCK, IPPROTO_TCP);
	if (sockfd < 0)
	{
		//log error
	}

	return sockfd;
}

void bindOrDie(int sockfd, const struct sockaddr* addr)
{
	if (::bind(sockfd, addr, sizeof (struct sockaddr_in)) < 0)
	{
		//log
		abort();
	}
}

int connect(int sockfd, const struct sockaddr* addr)
{
	return ::connect(sockfd, addr, static_cast<socklen_t>(struct sockaddr_in));
}

void listenOrDie(int sockfd)
{
	/*/proc/sys/net/somaxconn */
	if (::liten(sockfd, SOMAXCONN) < 0)
	{
		//log
		abort();
	}
}


