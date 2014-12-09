#include<iostream>
#include<set>
#include<algorithm>
#include<iterator>
using namespace std;

int main()
{
	//set<int> col2(op); //op设置排序的方式
	//不能给set容器中的元素重新复制，必须先删除，再添加新值， set容器的iterate为const
	typedef set<int, greater<int> > intset;
	set<int> col1;
	intset col2;
	col2.insert(4);
	col2.insert(3);
	col2.insert(5);
	col2.insert(1);
	col2.insert(6);
	col2.insert(2);
	col2.insert(5);

	intset::iterator iter;
	for (iter = col2.begin(); iter != col2.end(); ++iter)
	{
		cout << *iter << ' ';
	}
	cout << endl;

	pair<intset::iterator, bool> status = col2.insert(4);
	if (status.second)
	{
		cout << "4 inserter as element"
			 << distance(col2.begin(), status.first) * 1
			 << endl;
	}
	else
	{
		cout << "4 already exists" << endl;
	}

	set<int> col3(col2.begin(), col2.end());
	copy(col3.begin(), col3.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	col2.erase(col2.begin(), col2.find(3));

	int num;
	num = col2.erase(5);
	cout << num << " element(5) removed" << endl;

	copy(col2.begin(), col2.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;

}
