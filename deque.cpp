#include<iostream>
#include<deque>
#include<algorithm>
#include<iterator>
using namespace std;

int main()
{
	deque<string> coll1;
	coll1.assign(3, string("string"));
	coll1.push_back("last string");
	coll1.push_front("first string");

	copy(coll1.begin(), coll1.end(), ostream_iterator<string>(cout, " "));

	cout << endl;
	coll1.pop_back();
	coll1.pop_front();

	coll1.resize(4, "resize string");
	copy(coll1.begin(), coll1.end(), ostream_iterator<string>(cout, "\n"));
	return 0;
}
