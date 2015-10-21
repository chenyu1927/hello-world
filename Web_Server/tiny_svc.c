#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<strings.h>

#define MAXLINE 50

int doit(int fd);


int main(void)
{
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(66666);
	bind(sd, (struct sockaddr*)&addr, sizeof(addr));
	int err = listen(sd, 10);
	if (err)
	{
		return -1;
	}
	
	int cd = 0;
	int c_size = 0;
	struct sockaddr_in c_addr;
	bzero(&c_addr, sizeof(c_addr));
	while(1)
	{
		c_size = sizeof (c_addr);
		cd = accept(sd, (struct sockaddr*)&c_addr, &c_size);
		if (cd <= 0)
			break;

		doit(cd);
		close(cd);
	}
	
	return 0;
}

int doit(int fd)
{
	int is_static;
	char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
	int n = read(fd, buf, MAXLINE-1);
	sscanf(buf, "%s %s %s", method, uri, version);
	if (strcasecmp(method, "GET"))
	{
		return -1;
	}

	
}
