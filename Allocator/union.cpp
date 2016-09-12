#include <iostream>

using namespace std;

struct A
{
	bool b;
	int x;
};

struct B
{
	char c[8];
};

class C
{
public:



private:
	union
	{
		A a;
		B y;
	}
}
