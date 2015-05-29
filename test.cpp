#include"count_smart_ptr.h"
#include<iostream>
#include<memory>

using namespace std;

int main()
{
	Count_ptr<int> p(new int(9));
	auto_ptr<int> test_ptr(new int(8));

	cout << *test_ptr << endl;
	cout << *p << endl;

	Count_ptr<int> q(new int(0));
	Count_ptr<int> x(p);
	cout << *x << endl;
	cout << x.show_count() << endl;

	q = x;
	cout << *q << q.show_count() << endl;
	
	return 0;
}
