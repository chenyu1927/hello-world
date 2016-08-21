#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "Endian.h"
#include "SocketOps.h"
#include <errno.h>
#include <stdio.h>
#include "Type.h"
#include <strings.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int sockets::createNonblockingOrDie(sa_family_t family)
{
	int sockfd = ::socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
	if (sockfd < 0)
	{
		fprintf(stderr, "create sockfd error\n");
		abort();
	}

	return sockfd;
}

void sockets::bindOrDie(int sockfd, const struct sockaddr* addr)
{
	int ret = ::bind(sockfd, addr, static_cast<socklen_t>(sizeof (struct sockaddr_in6)));
	if (ret < 0)
	{
		fprintf(stderr, "bind sockfd in addr error\n");
		abort();
	}
}

void sockets::listenOrDie(int sockfd)
{
	int ret = ::listen(sockfd, SOMAXCONN);
	if (ret < 0)
	{
		fprintf(stderr, "listen sockfd error\n");
		abort();
	}
}

int sockets::accept(int sockfd, struct sockaddr_in* addr)
{
	socklen_t len = static_cast<socklen_t>(sizeof (struct sockaddr_in));
	int connfd = ::accept4(sockfd, sockaddr_cast(addr), &len, SOCK_NONBLOCK | SOCK_CLOEXEC);
	if (connfd < 0)
	{
		fprintf(stderr, "accept sockfd error or have while read finish\n");
//		abort();
	}

	return connfd;
}

int sockets::connect(int sockfd, const struct sockaddr* addr)
{
	return ::connect(sockfd, addr, 
			static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
}

ssize_t sockets::read(int sockfd, void* buf, size_t count)
{
	return ::read(sockfd, buf, count);
}

ssize_t sockets::write(int sockfd, const void* buf, size_t count)
{
	return ::write(sockfd, buf, count);
}

int sockets::close(int sockfd)
{
	return ::close(sockfd);
}

void sockets::shutdownWrite(int sockfd)
{
	int ret = ::shutdown(sockfd, SHUT_WR);
	if (ret < 0)
	{
		fprintf(stderr, "shutdown write error\n");
		abort();
	}
}

void sockets::toIpPort(char* buf, size_t size, const struct sockaddr* addr)
{
	toIp(buf, size, addr);
	const struct sockaddr_in* addr4 = sockaddr_in_cast(addr);
	uint16_t port = sockets::networkToHost16(addr4->sin_port);
	size_t len = strlen(buf);
	assert(size > len);
	snprintf(buf + len, size - len, ":%u", port );
}

void sockets::toIp(char* buf, size_t size, const struct sockaddr* addr)
{
	if (addr->sa_family == AF_INET)
	{
		assert(size >= INET_ADDRSTRLEN);
		const struct sockaddr_in* addr4 = sockaddr_in_cast(addr);
		::inet_ntop(AF_INET, &addr4->sin_addr, buf, 
				static_cast<socklen_t>(sizeof (struct sockaddr_in)));
	}
	else if(addr->sa_family == AF_INET6)
	{
		assert(size >= INET6_ADDRSTRLEN);
		const struct sockaddr_in6* addr6 = sockaddr_in6_cast(addr);
		::inet_ntop(AF_INET6, &addr6->sin6_addr, buf, 
				static_cast<socklen_t>(sizeof (struct sockaddr_in6)));
	}
}

void sockets::fromIpPort(const char* ip, uint16_t port, struct sockaddr_in* addr)
{
	addr->sin_family = AF_INET;
	addr->sin_port = sockets::hostToNetwork16(port);
	if (::inet_pton(AF_INET, ip, &addr->sin_addr) <= 0)
	{
		fprintf(stderr, "ip inet_pton error\n");
		abort();
	}
}

void sockets::fromIpPort(const char* ip, uint16_t port, struct sockaddr_in6* addr)
{
	addr->sin6_family = AF_INET6;
	addr->sin6_port = sockets::hostToNetwork16(port);
	if (::inet_pton(AF_INET6, ip, &addr->sin6_addr) != 1)
	{
		fprintf(stderr, "ip inet_pton AF_INET6 error\n");
		abort();
	}
}

int sockets::getSockError(int sockfd)
{
	int optval = 0;
	socklen_t optlen = static_cast<socklen_t>(sizeof optval);
	if (::getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
	{
		return errno;
	}
	else
	{
		return optval;
	}
}

const struct sockaddr* sockets::sockaddr_cast(const struct sockaddr_in* addr)
{
	return static_cast<const struct sockaddr*>(implicit_cast<const void*>(addr));
}

const struct sockaddr* sockets::sockaddr_cast(const struct sockaddr_in6* addr)
{
	return static_cast<const struct sockaddr*>(implicit_cast<const void*>(addr));
}

struct sockaddr* sockets::sockaddr_cast(struct sockaddr_in6* addr)
{
	return static_cast<struct sockaddr*>(implicit_cast<void*>(addr));
}

struct sockaddr* sockets::sockaddr_cast(struct sockaddr_in* addr)
{
	return static_cast<struct sockaddr*>(implicit_cast<void*>(addr));
}

const struct sockaddr_in* sockets::sockaddr_in_cast(const struct sockaddr* addr)
{
	return static_cast<const struct sockaddr_in*>(implicit_cast<const void*>(addr));
}

const struct sockaddr_in6* sockets::sockaddr_in6_cast(const struct sockaddr* addr)
{
	return static_cast<const struct sockaddr_in6*>(implicit_cast<const void*>(addr));
}

struct sockaddr_in6 sockets::getLocalAddr(int sockfd)
{
	struct sockaddr_in6 localaddr;
	bzero(&localaddr, sizeof localaddr);
	socklen_t socklen = static_cast<socklen_t>(sizeof (struct sockaddr_in6));
	if (::getsockname(sockfd, sockaddr_cast(&localaddr), &socklen) < 0)
	{
		fprintf(stderr, "getsockname error \n");
	}
	return localaddr;
}

struct sockaddr_in6 sockets::getPeerAddr(int sockfd)
{
	struct sockaddr_in6 peeraddr;
	bzero(&peeraddr, sizeof peeraddr);
	socklen_t len = static_cast<socklen_t>(sizeof peeraddr);
	if (::getpeername(sockfd, sockaddr_cast(&peeraddr), &len) < 0)
	{
		fprintf(stderr, "getpeername error\n");
	}

	return peeraddr;
}

bool sockets::isSelfConnect(int sockfd)
{
	struct sockaddr_in6 localaddr = getLocalAddr(sockfd);
	struct sockaddr_in6 peeraddr = getPeerAddr(sockfd);
	if (localaddr.sin6_family == AF_INET)
	{
		const struct sockaddr_in* laddr4 = reinterpret_cast<struct sockaddr_in*>(&localaddr    );
		const struct sockaddr_in* raddr4 = reinterpret_cast<struct sockaddr_in*>(&peeraddr)    ;
		return laddr4->sin_port == raddr4->sin_port
				&& laddr4->sin_addr.s_addr == raddr4->sin_addr.s_addr;
	}
	else if (localaddr.sin6_family == AF_INET6)
	{
		return localaddr.sin6_port == peeraddr.sin6_port
				&& memcmp(&localaddr.sin6_addr, &peeraddr.sin6_addr, sizeof localaddr.sin6_addr    ) == 0;
	}
	else
	{
		return false;
	}
}

