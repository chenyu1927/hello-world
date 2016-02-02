#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<sys/time.h>
#include<stdlib.h>

/*#include<sys/epoll.h>*/


int main(void)
{
	int srvfd, clifd;
	struct sockaddr_in srvaddr, cliaddr;
	socklen_t cli_len;
	struct timeval start;
	long int ustart;
	char buff[8];

	srvfd = socket(AF_INET, SOCK_STREAM, 0);
	if (srvfd < 0)
		return -1;
	
	bzero(&srvaddr, sizeof (struct sockaddr_in));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_port = htons(8888);
	inet_pton(AF_INET, "172.16.1.143", &(srvaddr.sin_addr));

	bind(srvfd, (struct sockaddr *)&srvaddr, sizeof (srvaddr));
	listen(srvfd, 100);

	for (;;)
	{
		clifd = accept(srvfd, (struct sockaddr*)&cliaddr, &cli_len);
		if (clifd > 0)
		{
			bzero(&start, sizeof (start));
			gettimeofday(&start, NULL);
			ustart = start.tv_sec * 1000000 + start.tv_usec;
			bzero(buff, sizeof (buff));
			memcpy(buff, &ustart, sizeof (long int));
			send(clifd, buff, strlen(buff), 0);
			shutdown(clifd, SHUT_WR);
		}
	}

	return 0;
}
