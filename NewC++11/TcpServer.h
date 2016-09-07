#ifndef TCPSERVER_H_H
#define TCPSERVER_H_H

#include <boost/noncopyable.hpp>
#include <memory>
#include <functional>
#include <string>
#include <atomic>
#include <map>
#include "Type.h"

class EventLoop;
class Acceptor;
class EventLoopThreadPool;
class InetAddress;

class TcpServer : boost::noncopyable
{
	
public:
	typedef std::function<void(EventLoop*)> ThreadInitCallback;

	enum Option
	{
		kNoReusePort,
		kReusePort,
	};

	TcpServer(EventLoop* loop, const InetAddress& listenAddr, 
			const std::string& nameArg, Option opt = kNoReusePort);

	~TcpServer();

	const std::string& ipPort() const { return ipPort_; }
	const std::string& name() const { return name_; }

	EventLoop* getLoop() const { return loop_; }
	void setThreadNums(int threadNums);
	std::shared_ptr<EventLoopThreadPool> threadPool() const
	{ return threadPool_; }

	void start();

	void setThreadInitCallback(ThreadInitCallback&& cb)
	{ threadInitCallback_ = cb; }

	void setConnectionCallback(ConnectionCallback&& cb)
	{ connectionCallback_ = cb; }

	void setWriteCompleteCallback(WriteCompleteCallback&& cb)
	{ writeCompleteCallback_ = cb; }

	void setMessageCallback(MessageCallback&& cb)
	{ messageCallback_ = cb; }


private:
	void newConnection(int sockfd, const InetAddress& peerAddr);
	void removeConnection(const TcpConnectionPtr& conn);
	void removeConnectionInLoop(const TcpConnectionPtr& conn);

	typedef std::map<std::string, TcpConnectionPtr> ConnectionMap;
	EventLoop* loop_;
//	InetAddress addr_;
	std::string ipPort_;
	std::string name_;
	std::unique_ptr<Acceptor> acceptor_;
	std::shared_ptr<EventLoopThreadPool> threadPool_;
	
	ConnectionCallback connectionCallback_;
	MessageCallback messageCallback_;
	WriteCompleteCallback writeCompleteCallback_;
	ThreadInitCallback threadInitCallback_;
	
	std::atomic<bool> started_;

	int nextConnId_;
	ConnectionMap connections_;
};







#endif //TCPSERVER_H_H
