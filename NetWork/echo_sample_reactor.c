//一个简单的reactor 的构造
#include "NetDefine.h"

#define MAXCONNS 20
//记录连接
struct Conn
{
	int sd; //sock id
	int is_used; //是否有效
};

typedef int (*handle_func)(void);
struct Handler{
	handle_func handler;
	int sd;
};

struct Conn conns[MAXCONNS];
struct Handler handlers[MAXCONNS];

int handle_input()
{
	return 0;
}

int handle_accept()
{
	return 0;
}

int handle_output()
{
	return 0;
}
