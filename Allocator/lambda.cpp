
#include <iostream>

using namespace std;

int main(void)
{
//	typedef function<size_t(function<size_t()>)>
//	auto func = [] (size_t n) -> size_t { return n > 0 ? n * func(n-1) : 1;};
//	auto p = [] (function<size_t (function<size_t()>)>)
	cout << func(5) << endl;
	return 0;
}
