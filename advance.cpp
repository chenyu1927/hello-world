#include<iostream>
#include<list>
#include<algorithm>
#include<iterator>
using namespace std;

int main()
{
	list<int> coll;
	for (int i = 0; i < 10; ++i)
	{
		coll.push_back(i);
	}

	list<int>::iterator pos = coll.begin();
	cout << *pos << endl;

	advance(pos, 3);
	cout << *pos << endl;

	advance(pos, -1);
	cout << *pos << endl;

	return 0;
}
