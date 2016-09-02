#include "Acceptor.h"
#include "EventLoop.h"
//#include <unistd.h>
#include <fcntl.h>
#include "InetAddress.h"
#include "SocketOps.h"
#include <unistd.h>
#include <stdio.h>

Acceptor::Acceptor(EventLoop* loop, const InetAddress& address, bool reusePort)
	: loop_(loop), acceptSocket_(sockets::createNonblockingOrDie(address.family())),
	  acceptChannel_(loop, acceptSocket_.fd()), listenning_(false),
	  idleFd_(::open("/dev/null", O_RDONLY | O_CLOEXEC))
{
	assert(acceptSocket_.fd() > 0);
	assert(acceptChannel_.fd() == acceptSocket_.fd());

	if (idleFd_ < 0)
	{
		fprintf(stderr, "system open /dev/null error\n");
		abort();
	}
	
//	acceptSocket_.setTcpNoDelay(true);
	acceptSocket_.setReuseAddr(true);
	acceptSocket_.setReusePort(reusePort);
	acceptSocket_.bindAddress(address);
	acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor()
{
	loop_->assertInLoopThread();

	listenning_ = false;
	acceptChannel_.disableAll();
	acceptChannel_.remove();
	::close(idleFd_);
}

void Acceptor::listen()
{
	loop_->assertInLoopThread();
	assert(!listenning_);
	listenning_ = true;
	acceptSocket_.listen();
	acceptChannel_.enableReading();
}

void Acceptor::handleRead()
{
	loop_->assertInLoopThread();
	assert(listenning_);
	
	InetAddress peeraddr;
//	while (true) //error cannot use while
	{
		int connfd = acceptSocket_.accept(&peeraddr);
		if (connfd >= 0)
		{
			if (newConnectionCallback_)
			{
				newConnectionCallback_(connfd, peeraddr);
			}
			else
			{
				sockets::close(connfd);
			}
		}
		else
		{
			if (errno == EMFILE) // accept socket max
			{
				::close(idleFd_);
				idleFd_ = ::accept(acceptSocket_.fd(), NULL, NULL);
				::close(idleFd_);
				idleFd_ = ::open("/dev/null", O_RDONLY | O_CLOEXEC);
			}
			//FIXME:has some do the error
		}
	}
}


