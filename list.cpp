#include<iostream>
#include<list>
#include<algorithm>
#include<iterator>
using namespace std;

int main()
{
	list<int> coll1;
	list<int> coll2;
	for (int i = 1; i < 10; ++i)
	{
		coll2.push_front(i);
		coll1.push_back(i);
	}

	copy(coll1.begin(), coll1.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	coll2.splice(find(coll2.begin(), coll2.end(), 3), coll1);
	//coll1.splice(coll1.begin(), coll2, coll2.end());
	copy(coll2.begin(), coll2.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	coll2.sort();

	//coll2 = coll1;
	copy(coll2.begin(), coll2.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	coll2.unique();
	copy(coll2.begin(), coll2.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	coll1.merge(coll2);
	copy(coll1.begin(), coll1.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	return 0;

}

