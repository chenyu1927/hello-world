#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#define MAXLINE 128

int main(int argc, char **argv)
{
	int sockfd, n;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;

	if (argc != 2)
	{
		printf("error: a.out <IPaddress>");
		return -1;
	}

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error");
		return -1;
	}

	bzero(&servaddr, sizeof (servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
	{
		printf("inet_pton error for %s", argv[1]);
		return -1;
	}

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof (servaddr)) < 0)
	{
		printf("connect error \n");
		exit(-1);
	}

	while ((n = read(sockfd, recvline, MAXLINE)) > 0)
	{
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF)
		{
			printf("fputs error");
		}
	}

	if (n < 0)
	{
		printf("read error");
	}
	close(sockfd);
	return 0;
}
