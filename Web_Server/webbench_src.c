#include<unistd.h>
#include<stdio.h>
#include<getopt.h>

int force = 0;
int force_reload = 0;
static const struct option long_options[] = 
{
	{"force",no_argument,&force,1},
	{"reload",no_argument, &force_reload,1},
	{NULL,0,NULL,0}
};

static void usage(void)
{
	fprintf(stderr,
		"web_bench [option]... URL\n"
		"   -f|--force				 Don't wait for reply from server.\n"
		"	-r|--reload				 Send reload request - Pragma:no-cache.\n"
	);
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		usage();
		return 2;
	}
	
	int opt = 0;
	int options_index = 0;
	while (opt = getopt_long(argc, argv, "912Vfrt:p:c:?h", long_options, &options_index))
	{
		switch (opt)
		{
		 case 0: break;
		 case 'f': force = 1;break;
		 case 'r': force_reload = 1; break;
		 case ':':
		 case 'h':
		 case '?': usage(); return 2; break;
		}
	}

	return 0;
}
