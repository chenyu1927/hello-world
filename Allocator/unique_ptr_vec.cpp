#include <memory>
#include <utility>
#include <iostream>
#include <vector>

using namespace std;

std::vector<unique_ptr<int>> unq_vec;
std::vector<int> vec;
void push(unique_ptr<int>&& it)
{
	unq_vec.push_back(std::move(it));
}

int main()
{

	unique_ptr<int> data(new int(10));

	push(std::move(data));

	vec.push_back(5);

	cout << "unique_ptr vecotr size = " << unq_vec.size() << endl;
//	for (auto item = unq_vec.begin(); item < unq_vec.end(); ++ item)
	for (auto&& item : unq_vec)
	{
		cout << "unique_ptr vector << " << (*item) << endl;
	}
	cout << "unique_ptr size = " << unq_vec.size() << endl;

	cout << "data = " << *(unq_vec[0]) << endl;

	for (auto iter : vec)
	{
		cout << iter << endl;
	}

	int* p = new int(9);
	unique_ptr<int> q1(p);
	unique_ptr<int> q2(p);
	
	if (q1 == q2)
	{
		cout << "true" << endl;
	}
	else
	{
		cout << "false" << endl;
	}
	
	return 0;
}
