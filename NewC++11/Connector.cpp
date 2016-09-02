#include "Connector.h"
#include "EventLoop.h"
#include "Channel.h"
#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include "SocketOps.h"

Connector::Connector(EventLoop* loop, const InetAddress& serveraddr)
	: loop_(loop), serveraddr_(serveraddr), connect_(false), 
	  state_(kDisconnected), retryDelayMs_(kInitRetryDelayMs)
{

}

Connector::~Connector()
{
	assert(!connChannel_);
}

void Connector::start()
{
	connect_ = true;
	loop_->runInLoop(std::bind(&Connector::startInLoop, this));
}

void Connector::startInLoop()
{
	loop_->assertInLoopThread();
	assert(state_ == kDisconnected);
	if (connect_)
	{
		connect();
	}
	else
	{
		fprintf(stderr, "do not connect\n");
	}
}

void Connector::stop()
{
	connect_ = false;
	loop_->runInLoop(std::bind(&Connector::stopInLoop, this));
}

void Connector::stopInLoop()
{
	loop_->assertInLoopThread();
	if (state_ == kConnecting)
	{
		setState(kDisconnected);
		int sockfd = removeAndResetChannel();
	}
}

int Connector::removeAndResetChannel()
{
	connChannel_->disableAll();
	connChannel_->remove();
	int sockfd = connChannel_->fd();
	loop_->queueInLoop(std::bind(&Connector::resetChannel, this));
	return sockfd;
}

void Connector::resetChannel()
{
	connChannel_.reset();
}

void Connector::connect()
{
	int sockfd = sockets::createNonblockingOrDie(serveraddr_.family());
	int ret = sockets::connect(sockfd, serveraddr_.getSockAddr());
	int saveErrno = (ret == 0) ? 0 : errno;
	switch (saveErrno)
	{
		case 0:
		case EINPROGRESS:
		case EINTR:
		case EISCONN:
			connecting(sockfd);
			break;

		case EAGAIN:
		case EADDRINUSE:
		case EADDRNOTAVAIL:
		case ECONNREFUSED:
		case ENETUNREACH:
			retry(sockfd);
			break;

		case EACCES:
		case EPERM:
		case EAFNOSUPPORT:
		case EALREADY:
		case EBADF:
		case EFAULT:
		case ENOTSOCK:
//			LOG_SYSERR << "connect error in Connector::startInLoop " << savedErrno;
			sockets::close(sockfd);
			break;

		default:
//			LOG_SYSERR << "Unexpected error in Connector::startInLoop " << savedErrno;
			sockets::close(sockfd);
			// connectErrorCallback_();
			break;
	}
}

void Connector::connecting(int sockfd)
{
	setState(kConnecting);
	assert(!connChannel_);

	connChannel_.reset(new Channel(loop_, sockfd));
	connChannel_->setWriteCallback(
			std::bind(&Connector::handleWrite, this));
	connChannel_->setErrorCallback(
			std::bind(&Connector::handleError, this));
	connChannel_->enableWriting();
}

void Connector::handleWrite()
{
	if (state_ == kConnecting)
	{
		int sockfd = removeAndResetChannel();
		int err = sockets::getSockError(sockfd);
		if (err)
		{
			fprintf(stderr, "Connector handleWrite error\n");
			retry(sockfd);
		}
		else if (sockets::isSelfConnect(sockfd))
		{
			retry(sockfd);
		}
		else
		{
			setState(kConnected);
			if (connect_)
			{
				newConnectionCallback_(sockfd);
			}
			else
			{
				sockets::close(sockfd);
			}
		}
	}
}

void Connector::handleError()
{
	if (state_ == kConnecting)
	{
		int sockfd = removeAndResetChannel();
		int err = sockets::getSockError(sockfd);

		fprintf(stderr, "Connector handleError\n");
		retry(sockfd);
	}
}

void Connector::restart()
{
	loop_->assertInLoopThread();

}

void Connector::retry(int sockfd)
{
	sockets::close(sockfd);
	setState(kDisconnected);
	if (connect_)
	{
		
	}
	else
	{

	}
}
