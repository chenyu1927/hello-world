#ifndef HTTP_SERVER_H_H
#define HTTP_SERVER_H_H

#include "TcpServer.h"

class EventLoop;
class InetAddress;
class HttpRequest;
class HttpRespond;

class HttpServer
{
public:
	typedef std::function<void(const HttpRequest*, HttpRespond*)> HttpCallback;

	HttpServer(EventLoop* loop, const InetAddress& listenAddr, 
			const std::string& name, TcpServer::Option option = TcpServer::kNoReusePort);

	~HttpServer();

	EventLoop* getLoop() { return server_.getLoop(); }

	void setHttpCallback(HttpCallback&& cb) { httpCallback_ = cb; }

	void setThreadNum(int threadNums) { server_.setThreadNums(threadNums); }

	void start();

private:
	void onConnection(const TcpConnectionPtr& conn);
	void onMessage(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp receiveTime);

	void onRequest(const TcpConnectionPtr&, const HttpRequest&);

	TcpServer server_;
	HttpCallback httpCallback_;
};









#endif //HTTP_SERVER_H_H
