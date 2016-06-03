#ifndef ACCEPTOR_H_H
#define ACCEPTOR_H_H

#include <boost/noncopyable.hpp>

class EventLoop;

class Acceptor : boost::noncopyable
{
public:
	Acceptor(EventLoop* loop);
	~Acceptor();

	void listen(const std::string& ip, const int8_t port);



private:
	void handleRead();

private:

	EventLoop* loop_;
	Socket	   acceptSocket_;
	Channel	   acceptChannel_;

	bool       listenning_;

};



















#endif /* ACCEPTOR_H_H */
