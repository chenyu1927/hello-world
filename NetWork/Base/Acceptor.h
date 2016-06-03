#ifndef ACCEPTOR_H_H
#define ACCEPTOR_H_H

#include <boost/noncopyable.hpp>
#include "Socket.h"
#include "Channel.h"

class EventLoop;
class InetAddress;

class Acceptor : boost::noncopyable
{
public:
	typedef boost::function(void(int sockfd, const InetAddress& addr)) NewConnectionCallback;

	Acceptor(EventLoop* loop);
	~Acceptor();

	void listen(const std::string& ip, const int8_t port);

	void setNewConnectionCallback(const NewConnectionCallback& cb)
	{
		newConnectionCallback_ = cb;
	}

private:
	void handleRead();

private:

	EventLoop* loop_;
	Socket	   acceptSocket_;
	Channel	   acceptChannel_;

	bool       listenning_;
	NewConnectionCallback newConnectionCallback_;
};



















#endif /* ACCEPTOR_H_H */
