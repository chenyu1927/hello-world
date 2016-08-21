#include "Socket.h"
#include "InetAddress.h"
#include "SocketOps.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>


Socket::~Socket()
{
	sockets::close(sockfd_);
}

void Socket::bindAddress(const InetAddress& localaddr)
{
	sockets::bindOrDie(sockfd_, localaddr.getSockAddr());
}

void Socket::listen()
{
	sockets::listenOrDie(sockfd_);
}

int Socket::accept(InetAddress* peeraddr)
{
	struct sockaddr_in addr;
	bzero(&addr, sizeof addr);

	int connfd = sockets::accept(sockfd_, &addr);
	if (connfd > 0)
	{
		peeraddr->setSockAddrInet4(addr);
	}

	return connfd;
}

void Socket::shutdownWrite()
{
	sockets::shutdownWrite(sockfd_);
}

void Socket::setReuseAddr(bool on)
{
	int optval = on ? 1 : 0;
	::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::setReusePort(bool on)
{
	int optval = on ? 1 : 0;
	::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::setTcpNoDelay(bool on)
{
	int optval = on ? 1 : 0;
	::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, &optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::setKeepAlive(bool on)
{
	int optval = on ? 1 : 0;
	::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE, &optval, static_cast<socklen_t>(sizeof optval));
}


