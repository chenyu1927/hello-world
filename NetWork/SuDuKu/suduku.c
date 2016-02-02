#include<stdio.h>

//回溯法求解9 * 9 的经典数独问题

#define N 81 //9 * 9个格子
#define NEIGHBOR 20 //相邻的格子


int board[N]; //棋盘
int spaces[N]; //空的格子，值代表下标
int neighbors[N][NEIGHBOR]; 
int nspaces;   // 最初的空格数

void reset()
{
	memset(borad, 0, sizeof (board));
	memset(space, 0, sizeof (space));
	nspace = 0;
}

void init_suduku(char *arr)
{
	int i;
	for (i = 0; i < N; ++i)
	{
		board[i] = arr[i];
		nspaces = 0;
		if (board[i] == 0)
		{
			nspaces += 1;
			spaces[i] = i;
		}
	}
}

int check_status()

char *solve_suduku(char *src)
{
	if (strlen(src) < N)
		return NULL;

	reset();
	init_suduku(src);
	if (nspace == 0)
	{
		return src;
	}
	else if (nspace > 0)
	{
	   
	}
	
}
