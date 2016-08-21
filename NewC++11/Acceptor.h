#ifndef ACCEPTOR_H_H
#define ACCEPTOR_H_H

#include <boost/noncopyable.hpp>
#include "Socket.h"
#include "Channel.h"
#include <functional>

class EventLoop;

class Acceptor : boost::noncopyable
{
public:
	typedef std::function<void(int sockfd, 
							   const InetAddress& address)> NewConnectionCallback;
	explicit Acceptor(EventLoop* loop, const InetAddress& listenaddr, bool reusePort = false);
	~Acceptor();

	void setNewConnectionCallback(const NewConnectionCallback& cb)
	{ newConnectionCallback_ = cb; }

	bool listenning() const { return listenning_; }
	void listen();

private:
	void handleRead();

	EventLoop* loop_;
	Socket acceptSocket_;
	Channel acceptChannel_; 
	NewConnectionCallback newConnectionCallback_;
	bool listenning_;
	int idleFd_;
};














#endif //ACCEPTOR_H_H
