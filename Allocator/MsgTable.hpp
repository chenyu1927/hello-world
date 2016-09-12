#include <unordered_map>
#include <functional>
#include <iostream>

using namespace std;

//typedef int (*Func) ();

typedef std::function<int ()> Callback;

class FuncTable
{
public:
	FuncTable()
	{}

	virtual ~FuncTable()
	{}

	void insert(const int key, const Callback& func)
	{
		auto iter = _func_table.find(key);
		if (iter == _func_table.end())
			_func_table.insert(std::make_pair(key, func));
	}

	void remove(const int key)
	{
		auto iter = _func_table.find(key);
		if (iter != _func_table.end())
			_func_table.erase(key);
	}

	Callback& getFunc(const int key)
	{
		auto iter = _func_table.find(key);
		if (iter != _func_table.end())
			return iter->second;
		else 
			return _defaultFunc;
	}

	void insertDefaultFunc(const Callback& func)
	{
		_defaultFunc = func;
	}


private:
	std::unordered_map<int, Callback> _func_table;
	Callback _defaultFunc;
};

class Handler
{
public:
	virtual ~Handler();
	void dispatch(const int key);
	virtual FuncTable* getFuncTable() = 0;
};

Handler::~Handler()
{

}

class Player
{
public:
	int func1()
	{
		cout << "func1()" << endl;
	}

	static int func2()
	{
		cout << "func2()" << endl;
	}
};

int func3()
{
	cout << "func3()" << endl;
}

void Handler::dispatch(const int key)
{
	Callback func = getFuncTable()->getFunc(key);
	if (func)
		func();
}

class Monitor : public FuncTable, public Handler
{
public:
	Monitor()
	{
//		insert(1, &Player::func1);
		insert(2, bind(&Player::func2));
		insert(3, bind(&func3));

		insertDefaultFunc(bind(&Monitor::defaultFunc, this));
	}

	int defaultFunc()
	{
		cout << "defaultFunc" << endl;
	}
	
	virtual FuncTable* getFuncTable()
	{
		return static_cast<FuncTable*>(this);
	}
};

