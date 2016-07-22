#include "TcpConnection.h"

TcpConnection::TcpConnection(EventLoop* loop, const string& name, int sockfd, const InetAddress& localAddr, const InetAddress& peerAddr)
	: loop_(loop),
	  name_(name),
	  state_(kConnecting),
	  socket_(new Socket(sockfd)),
	  channel_(new Channel(loop, sockfd)),
	  localAddr_(localAddr),
	  peerAddr_(peerAddr),
	  highWaterMark_(64*1024*1024),
	  reading_(true)
{
	channel_->setReadCallback(boost::bind(&TcpConnection::handleRead, this, _1));
	socket_->setKeepAlive(true);
}

void TcpConnection::send(const void* message, int len)
{
	send(StringPiece(static_cast<const char*>(message), len));
}

void TcpConnection::send(const StringPiece& message)
{
	if (state_ == kConnected)
	{
		sendInLoop(message);
	}
}

void TcpConnection::send(Buffer* buf)
{
	if (state_ == kConnected)
	{
		sendInLoop(buf->peek(), buf->readableBytes());
		buf->retrieveAll();
	}
}

void TcpConnection::sendInLoop(const StringPiece& message)
{
	sendInLoop(message.data(), message.size());
}

void TcpConnection::sendInLoop(const void* data, size_t len)
{
	ssize_t nwrote = 0;
	size_t remaining = len;
	bool faultError = false;
	if (state_ == kDisconnected)
	{
		return ;
	}

	if (!channel_->isWriting() && outputBuffer_.readableBytes() == 0)
	{
		nwrote = SocketOpt::write(channel_->fd(), data, len);
		if (nwrote >= 0)
		{
			remaining = len - nwrote;
			if (remaining == 0 && writeCompleteCallback_)
			{
				loop_->queueInLoop(boost::bind(writeCompleteCallback_, shared_frm_this()));
			}
		}
	}
}
