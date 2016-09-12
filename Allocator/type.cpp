#include <iostream>
#include <typeinfo>
using namespace std;

class Base
{
public:
	virtual ~Base() { }
private:
};

class X : public Base
{
public:
	X()
	: x(0)
	{ }

	virtual ~X() { }
private:
	int x;
};

class Y : public Base
{
public:
	Y()
	: y(false)
	{ }

	virtual ~Y() { }
private:
	bool y;
};

int sum(Base& a, Base& b)
{
	if (typeid(a) == typeid(b))
		return 1;
	else
		return 0;
}

int main()
{
	X x;
	Y y;
	X x1;

	cout << sum(x, y) << endl;
	cout << sum(x, x1) << endl;
	return 0;
}


