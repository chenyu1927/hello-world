
HttpServer.out : HttpServer_test.cpp HttpServer.cpp HttpRespond.cpp HttpContent.cpp TcpServer.cpp TcpConnection.cpp Buffer.cpp Timestamp.cpp Acceptor.cpp Socket.cpp SocketOps.cpp InetAddress.cpp EventLoopThreadPool.cpp EventLoopThread.cpp EventLoop.cpp TimerQueue.cpp Timer.cpp Epoller.cpp Channel.cpp Thread.cpp
	g++ -oHttpServer.out	 HttpServer_test.cpp HttpServer.cpp HttpRespond.cpp HttpContent.cpp TcpServer.cpp TcpConnection.cpp Buffer.cpp Timestamp.cpp Acceptor.cpp Socket.cpp SocketOps.cpp InetAddress.cpp EventLoopThreadPool.cpp EventLoopThread.cpp EventLoop.cpp TimerQueue.cpp Timer.cpp Epoller.cpp Channel.cpp Thread.cpp -std=c++11 -lpthread -lboost_system -g

TcpClient.out : TcpClient_test.cpp TcpClient.cpp TcpConnection.cpp Buffer.cpp Timestamp.cpp Connector.cpp Socket.cpp Epoller.cpp SocketOps.cpp InetAddress.cpp EventLoop.cpp TimerQueue.cpp Timer.cpp Channel.cpp Thread.cpp
	g++ -oTcpClient.out TcpClient_test.cpp TcpClient.cpp TcpConnection.cpp Buffer.cpp Timestamp.cpp Connector.cpp Epoller.cpp Socket.cpp SocketOps.cpp InetAddress.cpp EventLoop.cpp TimerQueue.cpp Timer.cpp Channel.cpp Thread.cpp -std=c++11 -lpthread -lboost_system -g

TcpServer.out : TcpServer_test.cpp TcpServer.cpp TcpConnection.cpp Buffer.cpp Timestamp.cpp Acceptor.cpp Socket.cpp SocketOps.cpp InetAddress.cpp EventLoopThreadPool.cpp EventLoopThread.cpp EventLoop.cpp TimerQueue.cpp Timer.cpp Epoller.cpp Channel.cpp Thread.cpp
	g++ -oTcpServer.out	 TcpServer_test.cpp TcpServer.cpp TcpConnection.cpp Buffer.cpp Timestamp.cpp Acceptor.cpp Socket.cpp SocketOps.cpp InetAddress.cpp EventLoopThreadPool.cpp EventLoopThread.cpp EventLoop.cpp TimerQueue.cpp Timer.cpp Epoller.cpp Channel.cpp Thread.cpp -std=c++11 -lpthread -lboost_system -g
	

TimerQueue.out :  TimerQueue_test.cpp TimerQueue.cpp Timer.cpp EventLoop.cpp Timestamp.cpp Epoller.cpp Channel.cpp Thread.cpp
	g++ -oTimerQueue.out TimerQueue_test.cpp TimerQueue.cpp Timer.cpp EventLoop.cpp Timestamp.cpp Epoller.cpp Channel.cpp Thread.cpp -std=c++11	-lboost_system -lpthread -g

Connector.out : Connector_test.cpp Connector.cpp SocketOps.cpp Buffer.cpp InetAddress.cpp EventLoop.cpp TcpConnection.cpp TimerQueue.cpp Socket.cpp Timer.cpp Channel.cpp Epoller.cpp Timestamp.cpp Thread.cpp
	g++ -oConnector.out Connector_test.cpp Connector.cpp SocketOps.cpp InetAddress.cpp TcpConnection.cpp Buffer.cpp TimerQueue.cpp Socket.cpp Timer.cpp EventLoop.cpp Channel.cpp Epoller.cpp  Timestamp.cpp Thread.cpp -std=c++11 -lboost_system -lpthread -g

Acceptor.out : Acceptor_test.cpp Acceptor.cpp Socket.cpp SocketOps.cpp InetAddress.cpp Buffer.cpp TcpConnection.cpp Timer.cpp TimerQueue.cpp Socket_test.cpp EventLoop.cpp EventLoopThread.cpp Timestamp.cpp Channel.cpp 
	g++ -oAcceptor.out Acceptor_test.cpp Acceptor.cpp Socket.cpp SocketOps.cpp InetAddress.cpp EventLoop.cpp Buffer.cpp Timer.cpp TimerQueue.cpp TcpConnection.cpp Channel.cpp EventLoopThread.cpp Timestamp.cpp	Epoller.cpp Thread.cpp -std=c++11 -lpthread -lboost_system 
Socket.out : Socket.cpp SocketOps.cpp InetAddress.cpp Socket_test.cpp EventLoop.cpp EventLoopThread.cpp Timestamp.cpp
	g++ -oSocket.out Socket_test.cpp Socket.cpp SocketOps.cpp InetAddress.cpp EventLoop.cpp Channel.cpp EventLoopThread.cpp Timestamp.cpp	Epoller.cpp Thread.cpp -std=c++11 -lpthread -lboost_system

EventLoopThreadPool.out : EventLoopThreadPool_test.cpp EventLoopThreadPool.cpp	EventLoopThread.cpp EventLoop.cpp Channel.cpp Epoller.cpp Timestamp.cpp Thread.cpp 
	g++ -o EventLoopThreadPool.out EventLoopThreadPool_test.cpp EventLoopThreadPool.cpp EventLoop.cpp EventLoopThread.cpp Channel.cpp Epoller.cpp Timestamp.cpp Thread.cpp -std=c++11 -lpthread -lboost_system

EventLoopThread.out : EventLoopThread_test.cpp EventLoopThread.cpp EventLoop.cpp Channel.cpp Epoller.cpp Timestamp.cpp  Thread.cpp
	g++ -o EventLoopThread.out EventLoopThread_test.cpp EventLoopThread.cpp EventLoop.cpp Channel.cpp Epoller.cpp Timestamp.cpp Thread.cpp -std=c++11 -lpthread -lboost_system

FileUntil.out : FileUntil.cpp FileUntil_test.cpp
	g++ -oFileUntil.out FileUntil.cpp FileUntil_test.cpp -std=c++11 -lboost_system

StringPiece.out : StringPiece_test.cpp
	g++ -oStringPiece.out StringPiece_test.cpp -std=c++11

thread_pool.out : ThreadPool_test.cpp ThreadPool.cpp Thread.cpp
	g++ -othread_pool.out ThreadPool_test.cpp ThreadPool.cpp Thread.cpp -pg -std=c++11 -lpthread -lboost_system
thread.out : Thread_test.cpp Thread.cpp
	g++ -othread.out Thread.cpp Thread_test.cpp -std=c++11 -lpthread

mutex.out : MutexLock_test.cpp Thread.cpp
	g++ -omutex.out MutexLock_test.cpp  Thread.cpp -std=c++11 -lpthread -lboost_system




cleanup:
	rm *.out
