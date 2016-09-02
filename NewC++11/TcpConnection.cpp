#include "TcpConnection.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include "SocketOps.h"

using namespace std::placeholders; // bind -> _1

TcpConnection::TcpConnection(EventLoop* loop, const std::string& name, int sockfd
		const InetAddress& localAddr, const InetAddress& peerAddr)
	: loop_(loop), state_(kDisconnected), socket_(new Socket(sockfd)),
	  channel_(new Channel(loop_, sockfd)), localAddr_(localAddr), peerAddr_(peerAddr), 
	  highWaterMark_(64*1024*1024), reading_(true)
{
	assert(sockfd >= 0);
	assert(socket_.fd() == channel_.fd());

	channel_.setReadCallback(std::bind(&TcpConnection::handleRead, this, _1));
	channel_.setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
	channel_.setCloseCallback(std::bind(&TcpConnection::handleClose, this));
	channel_.setErrorCallback(std::bind(&TcpConnection::handleError, this));
}

TcpConnection::~TcpConnection()
{
//	loop_->assertInLoopThread();
	assert(state_ == kDisconnected);
}

void TcpConnection::send(const void* message, int len)
{
	send(StringPiece(static_cast<const char*>(message), len));
}

void TcpConnection::send(const StringPiece& message)
{
	if (state_ == kConnected)
	{
		if (loop_->assertInLoopThread())
		{
			sendInLoop(message);
		}
		else
		{
			loop_->runInLoop(
					std::bind(&TcpConnection::sendInLoop, this, 
						std::forward<std::string>(message.to_string())));
		}
	}
}

void TcpConnection::send(Buffer* buffer)
{
	if (state_ == kConnected)
	{
		if (loop_->assertInLoopThread())
		{
			sendInLoop(buffer->peek(), buffer->readableBytes());
			buffer->retrieveAll();
		}
		else
		{
			loop_->runInLoop(std::bind(&TcpConnection::sendInLoop, this,
						buffer->retrieveAllAsString()));
		}
	}
}

void TcpConnection::send(Buffer&& buf)
{
	if (sate_ == kConnected)
	{
		if (loop_->assertInLoopThread())
		{
			sendInLoop(buf.peek(), buf.readableBytes());
			buf.retrieveAll();
		}
		else
		{
			loop_->runInLoop(std::bind(&TcpConnection::sendInLoop, this, 
						buf.retrieveAllAsString()));
		}
	}
}

void TcpConnection::sendInLoop(const StringPiece& message)
{
	sendInLoop(static_cast<const void*>(message.ptr()), message.size());
}

void TcpConnection::sendInLoop(const void* message, int len)
{
	loop_->assertInLoopThread();
//	assert(state_ == kConnected);
	if (state_ == kDisconnected)
	{
		fprintf(stderr, "Disconnected, give up write\n");
		return ;
	}
	
	ssize_t nWrote = 0;
	size_t remaining = len;
	bool faultError = false;

	if (!channel_->isWriting() && outputBuffer_.readableBytes() == 0)
	{
		nWrote = sockets::write(socket_.fd(), message, len);
		if (nWrote >= 0)
		{
			remaining = len - nWrote;
			if (remaining == 0 && writeCompleteCallback_)
			{
				loop_->queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
			}
		}
		else
		{
			nWrote = 0;
			if (errno != EWOULDBLOCK)
			{
				fprintf(stderr, "TcpConnection: sendInLoop error\n");
				if (errno == EPIPE || ECONNRESET)
				{
					faultError = true;
				}
			}
		}
	}

	assert(remaining <= len);
	if (!faultError && remaining > 0)
	{
		size_t oldLen = outputBuffer_.readableBytes();
		if (oldLen + remaining > highWaterMark_ && remaining < highWaterMark_ && highWaterMarkCallback_)
		{
			loop_->queueInLoop(std::bind(highWaterMarkCallback_, shared_from_this(), oldLen+remaining));
		}

		outputBuffer_.append(static_cast<const char*>(message)+nWrote, remaining);
		if (!channel_->isWriting())
			channel_->enableWriting();
	}
}

void TcpConnection::shutdown()
{
	if (state_ == kConnected)
	{
		setState(kDisconnecting);
		loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, this));
	}
}

void TcpConnection::shutdownInLoop()
{
	loop_->assertInLoopThread();
	if (!channel_->isWriting())
	{
		socket_->shutdownWrite();
	}
}

void TcpConnection::startRead()
{
	loop_->runInLoop(std::bind(&TcpConnection::startReadInLoop, this));
}

void TcpConnection::startReadInLoop()
{
	loop_->assertInLoopThread();
	if (!reading_ && !channel_->isReading())
	{
		channel_->enableReading();
		reading_ = true;
	}
}

void TcpConnection::stopRead()
{
	loop_->runInLoop(std::bind(&TcpConnection::stopReadInLoop, this));
}

void TcpConnection::stopReadInLoop()
{
	loop_->assertInLoopThread();
	if (reading_ && channel_->isReading())
	{
		channel_->disableReading();
		reading_ = false;
	}
}

void TcpConnection::forceClose()
{
	if (state_ == kConnected || state_ == kDisconnecting)
	{
		setState(kDisconnecting);
		loop_->queueInLoop(std::bind(&TcpConnection::forceCloseInLoop, shared_from_this()));
	}
}

void TcpConnection::forceCloseInLoop()
{
	loop_->assertInLoopThread();
	if (state_ == kConnected || state_ == kDisconnecting)
	{
		handleClose();
	}
}

void TcpConnection::forceCloseWithDelay(double second)
{
	if (state_ == kConnected || state_ == kDisconnecting)
	{

	}
}

void TcpConnection::setTcpNoDelay(bool on)
{

	socket_->setTcpNoDelay(on);
}

void TcpConnection::handleRead(Timestamp receviceTime)
{
	loop_->assertInLoopThread();
	int saveErrno = 0;
	ssize_t n = inputBuffer_.readFd(channel_.fd(), &saveErrno);
	if (n > 0)
	{
		messageCallback_(shared_from_this(), &inputBuffer_, receviceTime);
	}
	else if (n == 0)
	{
		handleClose(); // read return 0 --> peer is normal close
	}
	else 
	{
		handleError();
	}
}

void TcpConnection::handleClose()
{

}
