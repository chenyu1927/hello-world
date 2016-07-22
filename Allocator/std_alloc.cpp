#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main()
{
	allocator<string> alloc_str;
	string* const  p = alloc_str.allocate(10);
	string* q = p;

	alloc_str.construct(q++, "hello world!");
	alloc_str.construct(q, "chenyu");

	cout << *p << endl;
	cout << *(p+1) << endl;

	while (q != p)
		alloc_str.destroy(--q);

	alloc_str.deallocate(p, 10);

	allocator<int> alloc_int;
	vector<int> vec(5, 5);

	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	int* const pi = alloc_int.allocate(vec.size() * 2);
	int* pi2 = uninitialized_copy(vec.begin(), vec.end(), pi);
	uninitialized_fill_n(pi2, vec.size(), 6);
	for (size_t i = 0; i < vec.size() * 2; ++ i)
		cout << pi[i] << ' ';
	cout << endl;
	alloc_int.deallocate(pi, vec.size() * 2);
	return 0;
}
