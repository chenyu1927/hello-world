//#include "ThreadPool.h"
#include "Thread.h"
#include <iostream>
#include <vector>
#include <atomic>
#include <unistd.h>
//#include <memory>

using namespace std;

vector<int> vec;
atomic<bool> flag;

void reader_thread()
{
	while (!flag.load())
	{
		cout << "flag error" << endl;
//		sleep(1);
	}

	cout << "The answer = " << vec[0] << endl; 
}

void writer_thread()
{
	vec.push_back(27);
	flag = true;
}

int main()
{
	Thread thr_2(writer_thread, "writer_thread");
	Thread thr_1(reader_thread, "reader_thread");

	thr_2.start();
	thr_1.start();

	thr_2.join();
	thr_1.join();
	return 0;
//	unique_ptr<ThreadPool> tp_ptr(new ThreadPool());
//	tp_ptr->start(2);
}


