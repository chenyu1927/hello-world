#include <iostream>
using namespace std;

extern "C" void (*pfc)(void);
void (*pfc++)(void);

extern "C" void (*pfc2)(void(*)(void));

int main(void)
{
	pfc2(pfc++);	
//	pfc++ = pfc;

	return 0;
}

void pfc2(void(*func)(void))
{

}
