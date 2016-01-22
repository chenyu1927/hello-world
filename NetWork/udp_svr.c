#include<unistd.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
void dg_echo(int sockfd, struct sockaddr* pcliaddr, socklen_t clilen)
{
	int n;
	socklen_t len;
	char mesg[256];

	memset(mesg, 0, sizeof (mesg));
	for (; ;)
	{
		len = clilen;
		n = recvfrom(sockfd, mesg, sizeof (mesg), 0, pcliaddr, &len);
		sendto(sockfd, mesg, strlen(mesg), 0, pcliaddr, len);
	}
}

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in srvaddr, cliaddr;
	bzero(&srvaddr, sizeof (srvaddr));

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(7777);

	bind(sockfd, (struct sockaddr*)&srvaddr, sizeof (srvaddr));
	dg_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof (cliaddr));
	return 0;
}
