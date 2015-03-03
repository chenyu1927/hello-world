#include<iostream>
#include<iterator>
#include<list>
#include<algorithm>

using namespace std;

int main(void)
{
	list<int> coll;
	for (int i = 1; i < 10; ++i)
	{
		coll.push_back(i);

	}

	copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	iter_swap(coll.begin(), ++coll.begin());
	copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	iter_swap(coll.begin(), --coll.end());
	copy(coll.begin(), coll.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}
