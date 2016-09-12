#include "HttpServer.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "HttpRequest.h"
#include "HttpRespond.h"
#include "Timestamp.h"
#include "Buffer.h"
#include "TcpConnection.h"
#include "HttpContent.h"

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

namespace ext
{
	void defaultHttpCallback(const HttpRequest* req, HttpRespond* rsp)
	{
		rsp->setStatusCode(HttpRespond::k404NotFound);
		rsp->setStatusMessage("Not Found");
		rsp->setCloseConnection(true);
	}
}

HttpServer::HttpServer(EventLoop* loop, const InetAddress& listenAddr, const std::string& nameArg, TcpServer::Option option)
	: server_(loop, listenAddr, nameArg, option),
	  httpCallback_(ext::defaultHttpCallback)
{
	server_.setConnectionCallback(std::bind(&HttpServer::onConnection, this, _1));
	server_.setMessageCallback(std::bind(&HttpServer::onMessage, this, _1, _2, _3));
}

HttpServer::~HttpServer()
{

}

void HttpServer::start()
{
	server_.start();
}

void HttpServer::onConnection(const TcpConnectionPtr& conn)
{
	if (conn->connected())
	{
		conn->setContext(HttpContext());
	}
}

void HttpServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime)
{
	HttpContext* context = boost::any_cast<HttpContext>(conn->getMutableContext());

	if (!context->parseRequest(buf, receiveTime))
	{
		conn->send("HTTP1.1 400 bad request\r\n\r\n");
		conn->shutdown();
	}
	
	if (context->getAll())
	{
		onRequest(conn, context->request());
		context->reset();
	}
}

void HttpServer::onRequest(const TcpConnectionPtr& conn, const HttpRequest& request)
{
	const std::string connection = request.getHeader("connection");
	bool close = connection == "close" ||
		(request.getVersion() == HttpRequest::kHttp10 && connection != "Keep-Alive");

	HttpRespond respond(close);
	httpCallback_(&request, &respond);

	Buffer buf;
	respond.appendToBuffer(&buf);
	conn->send(&buf);
	if (respond.closeConnection())
	{
		conn->shutdown();
	}
}


