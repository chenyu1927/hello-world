#include "Connector.h"
#include "EventLoop.h"
#include "Channel.h"

Connector::Connector(EventLoop* loop, const InetAddress& serveraddr)
	: loop_(loop), serveraddr_(serveraddr), connect_(false), 
	  state_(kDisconnected), retryDelayMs_(0)
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
	assert(state == kDisconnected);
	if (connect_)
	{
		connect();
	}
	else
	{
		fprintf("do not connect\n");
	}
}

void Connector::restart()
{
	
}
