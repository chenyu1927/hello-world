#ifndef CONNECTOR_H_H
#define CONNECTOR_H_H

#include <boost/noncopyable.hpp>
#include <memory>
#include <functional>
#include "InetAddress.h"

class EventLoop;
class Channel;

class Connector : boost::noncopyable,
				  public std::enable_shared_from_this<Connector>
{
public:
	typedef std::function<void (int sockfd)> NewConnectionCallback;

	Connector(EventLoop* loop, const InetAddress& serveraddr);
	~Connector();

	void setNewConnectionCallback(NewConnection& cb)
	{ newConnectionCallback = cb; }

	void start(); 
	void restart();
	void stop();

private:
	enum States{
		kDisconnected, kConnecting, kConnected 
	};
	static const int kMaxRetryDelayMs = 30 * 1000;
	static const int kInitRetryDelayMs = 500;
	
	void setState(States state) { state_ = state; }
	void startInLoop();
	void stopInLoop();
	void connect();
	void connecting(int sockfd);
	void handleWrite();
	void handleError();
	void retry(int sockfd);
	int removeAndResetChannel();
	void resetChannel();

	EventLoop* loop_;
	InetAddress serveraddr_;
	bool	connect_;
	States  state_;
	std::unique_ptr<Channel> connChannel_;
	NewConnectionCallback newConnectionCallback_;
	int retryDelayMs_;
};


#endif // CONNECTOR_H_H
