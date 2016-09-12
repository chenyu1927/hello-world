#include "Query.hpp"
#include <vector>

int main(void)
{
	string file("test.txt");
	ifstream in(file);
	TextQuery query(in);

/*	string elem;
	cin >> elem;
	
	QueryResult res = query.runSearch(elem);
	res.printResult();*/

	Query q1("world");
	Query q2("chen");
	Query q3("what");
//	q1.eval(query).printResult();
	(q1 | q2).eval(query).printResult();

	cout << endl;

	((q1 & q2) | q3).eval(query).printResult();

	cout << endl;

	(~q1).eval(query).printResult();

	vector<int> t_v(5, 10);
	for (auto i : t_v)
		cout << i << ' ';
	cout << endl;
	return 0;
}
