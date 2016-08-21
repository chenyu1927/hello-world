#ifndef SOCKET_H_H
#define SOCKET_H_H

#include <boost/noncopyable.hpp>

class InetAddress;

class Socket : boost::noncopyable
{
public:
	explicit Socket(int sockfd)
		:sockfd_(sockfd)
	{}

	~Socket();
	const int fd() const { return sockfd_; }

	void bindAddress(const InetAddress& localaddr);

	void listen();

	int accept(InetAddress* peeraddr);

	void shutdownWrite();

	void setTcpNoDelay(bool on);

	void setReuseAddr(bool on);

	void setReusePort(bool on);

	void setKeepAlive(bool on);

private:
	const int sockfd_;
};







#endif /* SOCKET_H_H */
