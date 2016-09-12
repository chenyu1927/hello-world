#include "shared_ptr.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(void)
{
	self_shared_ptr<int> i(new int(10));
	cout << *i << endl;

	self_shared_ptr<int> n = i;

	self_shared_ptr<int> k(new int(0));
	k = n;
	cout << *k << endl;

	if (!k)
		cout << "nullptr" << endl;
	else
		return 0;

	self_shared_ptr<string> str(new string("chenyu"));
	cout << *str << endl;
	
	//k = str;
	return 0;
}
