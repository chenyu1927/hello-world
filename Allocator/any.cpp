#include <boost/any.hpp>
#include <iostream>
#include <string>
using namespace std;

int main()
{
	boost::any a;
	a = 10;

	cout << boost::any_cast<int>(a) << " " << a.type().name() << endl;


	boost::any b(string("chenyu"));
	cout << boost::any_cast<string>(b) << " " << b.type().name() << endl;
	return 0;
}
