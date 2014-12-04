#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>
using namespace std;

int main()
{
	vector<string> coll1;
	coll1.push_back("Hello,");
	coll1.push_back("how");
	coll1.push_back("are");
	coll1.push_back("you");
	coll1.push_back("?");
	copy(coll1.begin(), coll1.end(), ostream_iterator<string>(cout, " "));
	cout << endl;

	cout << coll1.max_size() << endl;
	cout << coll1.size() << endl;
	cout << coll1.capacity() << endl;
	swap(coll1[1], coll1[3]);
	coll1.insert(find(coll1.begin(), coll1.end(), "?"), "always");
	coll1.back() = "!";

	copy(coll1.begin(), coll1.end(), ostream_iterator<string>(cout, " "));
	vector<string> coll2;
	coll2.resize(coll1.size());
	copy(coll1.begin(), coll1.end(), coll2.begin());



	copy(coll1.begin(), coll1.end(), ostream_iterator<string>(cout, " "));


	return 0;
}
