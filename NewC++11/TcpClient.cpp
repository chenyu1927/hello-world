#include "TcpClient.h"
#include "Connector.h"
#include <assert.h>
#include "TcpConnection.h"
#include "EventLoop.h"
#include "SocketOps.h"

namespace ext
{
	void removeConnection(EventLoop* loop, const TcpConnectionPtr& conn)
	{
		loop->runInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
	}
}

using std::placeholders::_1;

TcpClient::TcpClient(EventLoop* loop, const InetAddress& serverAddr, const std::string& nameArg)
	: loop_(loop), connector_(new Connector(loop, serverAddr)), name_(nameArg), 
	  connectionCallback_(defaultConnectionCallback), messageCallback_(defaultMessageCallback), 
	  retry_(false), connect_(false), nextConnId_(1), mutex_()
{
	assert(loop_);
	connector_->setNewConnectionCallback(
			std::bind(&TcpClient::newConnection, this, _1));
}

TcpClient::~TcpClient()
{
	TcpConnectionPtr conn;
	bool unique = false;

	{
		MUTEX_GUARD(mutex_,obj);
		unique = connection_.unique();
		conn = connection_;
	}

	if (conn)
	{
		assert(loop_ == conn->getLoop());
		CloseCallback cb = std::bind(&ext::removeConnection, loop_, _1);
		loop_->runInLoop(std::bind(&TcpConnection::setCloseCallback, conn, cb));

		if (unique)
		{
			conn->forceClose();
		}
	}
	else
	{
		connector_->stop();
	}
}

void TcpClient::connect()
{
	assert(!connect_);
	connect_ = true;
	connector_->start();
}

void TcpClient::stop()
{
	connect_ = false;
	connector_->stop();
}

void TcpClient::newConnection(int sockfd)
{
	loop_->assertInLoopThread();
	InetAddress peerAddr(sockets::getPeerAddr(sockfd));
	char buf[64] = {0};
	snprintf(buf, sizeof buf, "-%s#%d", peerAddr.toIpPort().c_str(), nextConnId_);
	++ nextConnId_;
	std::string	connName = name_ + buf;
	InetAddress localAddr(sockets::getLocalAddr(sockfd));
	TcpConnectionPtr conn(new TcpConnection(loop_, connName, sockfd, localAddr, peerAddr));
	conn->setConnectionCallback(connectionCallback_);
	conn->setMessageCallback(messageCallback_);
	conn->setCloseCallback(std::bind(&TcpClient::removeConnection, this, _1));

	{
		MUTEX_GUARD(mutex_, obj);
		connection_ = conn;
	}
	
//	loop_->runInLoop(std::bind(&TcpConnection::connectEstablished, connection_));
	conn->connectEstablished();
//	conn->send("Hi, how are you?");
}

void TcpClient::removeConnection(const TcpConnectionPtr& conn)
{
	loop_->assertInLoopThread();
	assert(loop_ == conn->getLoop());

	{
		MUTEX_GUARD(mutex_, obj);
		assert(connection_ == conn);
		connection_.reset();
	}

	loop_->queueInLoop(std::bind(&TcpConnection::connectDestroyed, conn));

	if (retry_ && connect_)
	{
		connector_->restart();
	}
}


