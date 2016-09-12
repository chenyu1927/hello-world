#include <functional>

using namespace std;

void func(int x)
{
	x++;
}

void func()
{

}

typedef function<void()> Functor;

int main(void)
{
	Functor f1(std::bind(static_cast<void(*)(int)>(&func), placeholders::_1));
	return 0;
}
