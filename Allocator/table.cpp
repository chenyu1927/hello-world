#include <unordered_map>
#include <functional>
#include <iostream>
#include <memory>

using namespace std;

//typedef int (*Func) (); //FIXME:error
class Handler;
typedef int (Handler::*Func)();

typedef std::function<int ()> Callback;

class FuncTable
{
public:
	FuncTable()
		: _defaultFunc(nullptr)
	{

	}

	virtual ~FuncTable()
	{}

	void insert(const int key, Func func)
	{
		auto iter = _func_table.find(key);
		if (iter == _func_table.end())
			_func_table.insert(std::make_pair(key, func));
	}

	template <typename T>
	void insert(const int key, T func)
	{
/*		if (_func_table.find(key) == _func_table.end())
		{
			Func f = static_cast<Func>(func);
			if (f)
			{
				_func_table.insert(std::make_pair(key, f));
			}
		}*/
		insert(key, static_cast<Func>(func));
	}

	void remove(const int key)
	{
		auto iter = _func_table.find(key);
		if (iter != _func_table.end())
			_func_table.erase(key);
	}

	Func getFunc(const int key)
	{
		auto iter = _func_table.find(key);
		if (iter != _func_table.end())
			return iter->second;
		else 
			return _defaultFunc;
	}

	void insertDefaultFunc(Func func)
	{
		_defaultFunc = func;
	}
	
	template <typename T>
	void insertDefaultFunc(T func)
	{
		insertDefaultFunc(static_cast<Func>(func));
	}

private:
	std::unordered_map<int, Func> _func_table;
	Func _defaultFunc;
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

class Player : public Handler
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

/*int func3()
{
	cout << "func3()" << endl;
}*/

void Handler::dispatch(const int key)
{
	Func func = getFuncTable()->getFunc(key);
	if (func != nullptr)
		(this->*(func))();
}

class Monitor : public FuncTable, public Handler
{
public:
	Monitor()
	{
		insert(1, &Player::func1);
//		insert(2, &Player::func2);
//		insert(3, func3);

		insertDefaultFunc(&Monitor::defaultFunc);
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

int main(void)
{
//	shared_ptr<Monitor> monitor(new Monitor);
	shared_ptr<Monitor> monitor = make_shared<Monitor>();
	int i;
	cin >> i;

	monitor->dispatch(i);
	return 0;
}
