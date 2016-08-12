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
