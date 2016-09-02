#ifndef TCPCONNECTION_H_H
#define TCPCONNECTION_H_H

#include <boost/noncopyable.hpp>
#include <boost/any.hpp>
#include "Buffer.h"
#include "InetAddress.h"
#include <memory>

class EventLoop;
class Socket;
class Channel;
//class InetAddress;

class TcpConnection : boost::noncopyable,
					  public std::enable_shared_from_this<TcpConnection>
{
public:
	TcpConnection(EventLoop* loop, const std::string& name
			int sockfd, const InetAddress& localAddr, const InetAddress& peerAddr);
	~TcpConnection();

	EventLoop* getLoop() const { return loop_; }
	const std::string& name() const { return name_; }
	const InetAddress& localAddress() const { return localAddr_; }
	const InetAddress& peerAddress() const { return peerAddr_; }

	bool connected() const { return state_ == kConnected; }
	bool disconnected() const { return state_ == kDisconnected; }

//	bool getTcpInfo(struct ) 
	
	void send(const void* message, int len);
	void send(const StringPiece& message);
	void send(Buffer* message);
	void send(Buffer&& message);

	void shutdown();

	void forceClose();
	void forceCloseWithDelay(double seconds);
	void setTcpNoDelay(bool on);

	void startRead();
	void stopRead();
	bool isReading() const { return reading_; }

	void setContext(const boost::any& context) { context_ = context; }
	const boost::any& getContext() const { return context_; }
	boost::any* getMutableContext() { return &context_; }
	
	void setConnectionCallback(const ConnectionCallback& cb) { connectionCallback_ = cb; }
	void setMessageCallback(const MessageCallback& cb) { messageCallback_ = cb; }
	void setWriteCompleteCallback(const WriteCompleteCallback& cb) { writeCompleteCallback_ = cb; }


	Buffer* inputBuffer() { return &inputBuffer_; }
	Buffer* outputBuffer() { return &outputBuffer_; }

	void setCloseCallback(const CloseCallbakc& cb) { closeCallback_ = cb; }

	void connectEstablished();
	void connectDestroyed();


private:
	enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting, }
	
	void handleRead(Timestamp receviceTime);
	void handleWrite();
	void handleClose();
	void handleError();

	void sendInLoop(const StringPiece& message);
	void sendInLoop(const void* message, int len);
	void shutdownInLoop();

	void startReadInLoop();
	void stopReadInLoop();

	EventLoop* loop_;
	const std::string name_;
	StateE state_;

	std::unique_ptr<Socket> socket_;
	std::unique_ptr<Channel> channel_;

	const InetAddress localAddr_;
	const InetAddress peerAddr_;

	ConnectionCallback connectionCallback_;
	MessageCallback messageCallback_;
	WriteCompleteCallback writeCompleteCallback_;
	HighWaterMarkCallback highWaterMarkCallback_;
	CloseCallback closeCallback_;

	size_t highWaterMark_;
	Buffer	inputBuffer_;
	Buffer  outputBuffer_;
	boost::any context_; //std c++17
	bool reading_;
};












#endif //TCPCONNECTION_H_H
