#include "ThreadPool.h"
#include "ThreadLocal.h"
#include "CurrentThread.h"
#include <iostream>
#include <string>

using namespace std;

//ThreadLocal<string> t_local;

void func()
{
//	t_local.value() = "func";
	auto i = 10;
	while (i > 0)
	{
		cout << static_cast<char>('a' + i) << " ";
		--i;
	}

	cout << CurrentThread::name() << " " << CurrentThread::tid() << CurrentThread::isMainThread() << endl;
//	cout << "t_local=" << t_local.value() << endl;
}

int main()
{
//	Thread thread([] {auto i = 10; while (i > 0)
//			cout << i-- << " "; cout << CurrentThread::name() << endl;});
	cout << CurrentThread::name() << endl;
	ThreadLocal<string> t_local;
	t_local.value() = "main";

	ThreadPool t_pool;
	t_pool.setMaxQueueSize(100);

	t_pool.start(4);

	t_pool.addTask(std::move(func));
	t_pool.addTask([&] {t_local.value() = "lambda"; auto i = 10; while (i > 0) cout << i-- << " "; cout << CurrentThread::name() << endl;});

	cout << "t_local=" << t_local.value() << endl;
//	Thread thread1(func);


//	thread.start();
//	thread1.start();

//	thread1.join();
//	thread.join();

	return 0;
}
