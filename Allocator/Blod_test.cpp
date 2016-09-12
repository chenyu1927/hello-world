#include <iostream>
#include "Blod.hpp"
using std::cout;
using std::endl;

int main(void)
{
	Blod<int> i = {4, 6, 7, 8, 9};
	cout << "size=" << i.size() << endl;

	try
	{
		cout << i[5] << endl;
	}
	catch (std::out_of_range& e)
	{
		cout << e.what() << endl;
	}
	
	std::vector<int> vec(5, 6);
	Blod<int> v(vec.begin(), vec.end());
	cout << "v.size=" <<v.size() << endl;
//	cout << i[3] << endl;
	return 0;
}

