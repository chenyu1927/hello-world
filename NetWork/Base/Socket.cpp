#include "Socket.h"
#include <unistd.h>

Socket::~Socket()
{
	::close(sockfd_);
}

void Socket::bindAddress(const InetAddress& localaddr)
{
	socketopt::bindOrDie(sockfd_, localaddr.getSockAddr());
}

void Socket::listen()
{
	sockopt::listenOrDie(sockfd_);
}

void Socket::setTcpNoDelay(bool on)
{
	int optval = on ? 1 : 0;
	::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY, 
			&optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::setReuseAddr(bool on)
{
	int optval = on ? 1 : 0;
	::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, 
			&optval, static_cast<socklen_t>sizeof optval);

}

