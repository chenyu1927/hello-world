#include "Acceptor.h"
#include "SocketsOpt.h"

Acceptor::Acceptor(EventLoop* loop)
	: loop_(loop),
	  acceptSocket_(socketopt::createNonblockingOrDie(AF_INET)),
	  acceptChannel_(loop, acceptSocket_),
	  listenning_(false)
{
	assert(acceptSocket_ > 0);
	acceptChannel_.setReadCallBack(boost::bind(&Acceptor::handlRead, this));
	acceptChannel_.enableReading();
}

Acceptor::~Acceptor()
{
	acceptChannel_.disableAll();
	acceptChannel_.remove();

}

void Acceptor::listen(StringArg ip, uint16_t port)
{
//	assert(port > 1024);
	assert(!listenning_);
	listenning_ = true;

	InetAddress localaddr(ip, port);
	acceptSocket_.bindAddress(InetAddress);
	acceptSocket_.listen();

//	acceptChannel_.setReadCallBack(boost::bind(&Acceptor::handlRead, this));
//	acceptChannel_.enableReading();
}

void Acceptor::handlRead()
{	
	InetAddress peeraddr;
	int connfd = acceptSocket_.accept(&peeraddr);
	if (connfd >= 0)
	{
		if (newConnectionCallback_)
		{
			newConnectionCallback_(connfd, peeraddr);
		}
		else
		{
			::close(connfd);
		}
	}
	else
	{
		//log

		if (errno == EMFILE)
		{

		}
	}
}

