#ifndef TCP_CLIENT_H_H
#define TCP_CLIENT_H_H

#include <boost/noncopyable.hpp>
#include <string>
#include <memory>
#include "Type.h"
#include "MutexLock.h"

class Connector;
typedef std::shared_ptr<Connector> ConnectorPtr;
class EventLoop;
class InetAddress;
class TcpClient : boost::noncopyable
{
public:
	TcpClient(EventLoop* loop, const InetAddress& serverAddr, const std::string& nameArg);
	~TcpClient();

	void connect();
	void disconnect();
	void stop();

	TcpConnectionPtr connection() const 
	{
		MUTEX_GUARD(mutex_, obj);
		return connection_;
	}

	EventLoop* getLoop() const { return loop_; }
	bool retry() const { return retry_; }
	void enableRetry() { retry_ = true; }

	const std::string& name() const { return name_; }

	void setConnectionCallback(ConnectionCallback&& cb)
	{ connectionCallback_ = std::move(cb); }

	void setMessageCallback(MessageCallback&& cb)
	{ messageCallback_ = std::move(cb); }

	void setWriteCompleteCallback(WriteCompleteCallback&& cb)
	{ writeCompleteCallback_ = std::move(cb); }


private:
	
	void newConnection(int sockfd);
	void removeConnection(const TcpConnectionPtr& conn);

	EventLoop* loop_;
	ConnectorPtr connector_;
	const std::string name_;

	ConnectionCallback connectionCallback_;
	MessageCallback messageCallback_;
	WriteCompleteCallback writeCompleteCallback_;

	bool retry_;
	bool connect_;

	int nextConnId_;
	mutable MutexLock mutex_;

	TcpConnectionPtr connection_;
};

























#endif //TCP_CLIENT_H_H
