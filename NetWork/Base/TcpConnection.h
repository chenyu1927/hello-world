#ifndef TCPCONNECTOR_H_H
#define TCPCONNECTOR_H_H

#include "Socket.h"
#include "Buffer.h"
#include "InetAddress.h"

#include <boost/noncopyable.hpp>
#include <boost/any.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

class Socket;
class EventLoop;
class Channel;

//TcpConnection for both server and client
//
class TcpConnection : boost::noncopyable,
					  public boost::enable_shared_from_this<TcpConnection>
{
public:

	TcpConnection(EventLoop* loop, const string& name, int sockfd, const InetAddress& localAddr, const InetAddress& peerAddr);
	~TcpConnection();
	
	EventLoop* getLoop() const { return loop_; }
	const string& name() const { return name_; }
	const InetAddress& localAddress() const { return localAddr_; }
	const InetAddress& peerAddress() const { return peerAddr_; }

	bool connected() const { return state_ == kConnected; }
	bool disconnected() const { return state_ == kDisconnected; }

	void send(const void* message, int len);
	void send(const StringPiece& message);

	void send(Buffer* message);
	void shutdown();

	void forceClose();
	void forceCloseWithDelay(double seconds);
	void setTcpNoDelay(bool on);
	void startRead();
	void stopRead();
	bool isReading() const { return reading_; }

private:
	enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };

	EventLoop* loop_;
	const string name_;
	StateE state_;  
	boost::scoped_ptr<Socket> socket_;
	boost::scoped_ptr<Channel> channel_;
	const InetAddress localAddr_;
	const InetAddress peerAddr_;
	ConnectionCallback connectionCallback_;
	MessageCallback messageCallback_;
	CloseCallback closeCallback_;
	size_t highWaterMark_;
	Buffer inputBuffer_;
	Buffer outputBuffer_;
	boost::any context_;
	bool reading_;
};

typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;










#endif /*TCPCONNECTIOR_H_H */
