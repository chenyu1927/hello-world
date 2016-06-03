#include "SocketsOpt.h"
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include "type.h"

int socketopt::createNonblockingOrDie(sa_family_t family)
{
	int sockfd = ::socket(family, SOCK_STREAM | SOCK_CLOEXEC | SOCK_NONBLOCK, IPPROTO_TCP);
	if (sockfd < 0)
	{
		//log error
	}

	return sockfd;
}

void socketopt::bindOrDie(int sockfd, const struct sockaddr* addr)
{
	if (::bind(sockfd, addr, sizeof (struct sockaddr_in)) < 0)
	{
		//log
		abort();
	}
}

int socketopt::connect(int sockfd, const struct sockaddr* addr)
{
	return ::connect(sockfd, addr, static_cast<socklen_t>(struct sockaddr_in));
}

void socketopt::listenOrDie(int sockfd)
{
	/*/proc/sys/net/somaxconn */
	if (::liten(sockfd, SOMAXCONN) < 0)
	{
		//log
		abort();
	}
}

void socketopt::fromIpPort(const char* ip, uint16_t port, struct sockaddr_in* addr)
{
	addr->sin_family = AF_INET;
	addr->sin_port = ::htons(port);
	if (::inet_pton(AF_INET, ip, static_cast<void*>(&addr->sin_addr.s_addr)) < 0)
	{
		//FIXME: log
	}
}

int socketopt::accept(int sockfd, struct sockaddr_in* addr)
{
	socklen_t len = static_cast<socklen_t>(sizeof *addr);

	int fd = ::accept4(sockfd, sockaddr_cast(addr), &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
	if (fd < 0)
	{
		//log
		int saveErrno = errno;
		switch(saveErrno)
		{
		  case EAGAIN:
		  case EINTR:
			  //log
			  break;
		}
	}

	return fd;
}

ssize_t socketopt::read(int sockfd, void* buf, size_t count)
{
	return ::read(sockfd, buf, count);
}

ssize_t socketopt::write(int sockfd, void* buf, size_t count)
{
	return ::write(sockfd, buf, count);
}

void socketopt::close(int sockfd)
{
	if (::close(sockfd) < 0)
	{
		//log
	}
}

void socketopt::shutdownWrite(int sockfd)
{
	if (::shutdown(sockfd, SHUT_WR) < 0)
	{
		//log
	}
}

int socketopt::getSocketError(int sockfd)
{
	int optval;
	socklen_t optlen = static_cast<socklen_t>(sizeof optval);
	if (::getsockopt(sockfd, SOL_SOCKET, SOL_ERROR, &optval, &optlen) < 0)
	{
		return errno;
	}
	else
		return optval;
}

struct sockaddr_in socketopt::getLocalAddr(int sockfd)
{
	struct sockaddr_in localaddr;
	bzero(&localaddr, sizeof localaddr);
	socklen_t addrlen = static_cast<socklen_t>(sizeof localaddr);
	if (::getsockname(sockfd, sockaddr_cast(&localaddr), &addrlen) < 0)
	{
		//log
	}

	return localaddr;
}

struct sockaddr_in socketopt::getPeerAddr(int sockfd)
{
	struct sockaddr_in peeraddr;
	bzero(&peeraddr, sizeof peeraddr);
	socklen_t addrlen = static_cast<socklen_t>(sizeof peeraddr);
	if (::getpeername(sockfd, sockaddr_cast(&peeraddr), &addrlen) < 0)
	{
		//log
	}

	return peeraddr;
}

const struct sockaddr* socketopt::sockaddr_cast(const struct sockaddr_in* addr)
{
	return static_cast<const struct sockaddr*>(implicit_cast<const void*>(addr));
}

const struct sockadd_in* socketopt::sockaddr_in_cast(const struct sockaddr* addr)
{
	return static_cast<const struct sockaddr_in*>(implicit_cast<const void*>(addr));
}


