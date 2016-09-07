#include "TcpServer.h"
#include "Acceptor.h"
#include "EventLoopThreadPool.h"
#include "EventLoop.h"
#include "TcpConnection.h"
#include "InetAddress.h"
#include "SocketOps.h"

using std::placeholders::_1;
using std::placeholders::_2;

TcpServer::TcpServer(EventLoop* loop, const InetAddress& address, const std::string& nameArg, Option opt)
	: loop_(loop), ipPort_(address.toIpPort()), name_(nameArg), acceptor_(new Acceptor(loop_, address, opt)),
	  threadPool_(new EventLoopThreadPool(loop_, name_)), connectionCallback_(defaultConnectionCallback),
	  messageCallback_(defaultMessageCallback), started_(false), nextConnId_(1)
{
	acceptor_->setNewConnectionCallback(std::bind(&TcpServer::newConnection, this, _1, _2));
}

TcpServer::~TcpServer()
{
	loop_->assertInLoopThread();

	for (auto iter : connections_)
	{
		TcpConnectionPtr conn = iter.second;
		iter.second.reset();
		conn->getLoop()->runInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
		conn.reset();
	}
}

void TcpServer::setThreadNums(int threadNums)
{
	assert(0 <= threadNums);
	threadPool_->setNumThreads(threadNums);
}

void TcpServer::start()
{
	if (!started_.exchange(true))
	{
//		started_ = true;
		threadPool_->start(threadInitCallback_);

		assert(!acceptor_->listenning());
		loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));
	}
}

void TcpServer::newConnection(int sockfd, const InetAddress& address)
{
	loop_->assertInLoopThread();
	EventLoop* ioLoop = threadPool_->getNextLoop();
	char buf[64];
	snprintf(buf, sizeof buf, "-%s#%d", ipPort_.c_str(), nextConnId_);
	++nextConnId_;
	std::string connName = name_ + buf;
	fprintf(stderr, "new connection fd = %d name = %s \n", sockfd, connName.c_str());
	InetAddress localAddr(sockets::getLocalAddr(sockfd));

	TcpConnectionPtr conn = std::make_shared<TcpConnection>(ioLoop, connName, sockfd, localAddr, address);
	connections_[connName] = conn;
	conn->setConnectionCallback(connectionCallback_);
	conn->setMessageCallback(messageCallback_);
	conn->setWriteCompleteCallback(writeCompleteCallback_);
	conn->setCloseCallback(
			std::bind(&TcpServer::removeConnection, this, _1));
	ioLoop->runInLoop(std::bind(&TcpConnection::connectEstablished, conn));
}

void TcpServer::removeConnection(const TcpConnectionPtr& conn)
{
	loop_->runInLoop(std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}

void TcpServer::removeConnectionInLoop(const TcpConnectionPtr& conn)
{
	loop_->assertInLoopThread();

	size_t n = connections_.erase(conn->name());
	assert(n == 1);

	EventLoop* ioLoop = conn->getLoop();
	ioLoop->runInLoop(
			std::bind(&TcpConnection::connectDestroyed, conn));

}


