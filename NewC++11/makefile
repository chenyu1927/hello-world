Acceptor.out : Acceptor_test.cpp Acceptor.cpp Socket.cpp SocketOps.cpp InetAddress.cpp Socket_test.cpp EventLoop.cpp EventLoopThread.cpp Timestamp.cpp Channel.cpp 
	g++ -oAcceptor.out Acceptor_test.cpp Acceptor.cpp Socket.cpp SocketOps.cpp InetAddress.cpp EventLoop.cpp Channel.cpp EventLoopThread.cpp Timestamp.cpp	Epoller.cpp Thread.cpp -std=c++11 -lpthread -lboost_system 
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
