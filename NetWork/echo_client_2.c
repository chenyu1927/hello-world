#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/select.h>

void str_cli(FILE *fp, int sockfd)
{
  char sendline[256], recvline[256];
  bzero(sendline, 256);
  bzero(recvline, 256);
  while (fgets(sendline, 256, fp) != NULL)
  {
	send(sockfd, sendline, 1, 0);
	sleep(1);
    send(sockfd, sendline+1, strlen(sendline) - 1, 0);
    if (recv(sockfd, recvline, 256, 0) == 0)
      return;
    fputs(recvline, stdout);
	bzero(sendline, 256);
	bzero(recvline, 256);
  }
}
void str_cli_1(FILE *fp, int sockfd)
{
	int max_fd, stdineof, n;
	fd_set set;
	char buff[256];

	bzero(buff, 256);
	FD_ZERO(&set);
	stdineof = 0;
	for (; ;)
	{
		if (stdineof == 0)
			FD_SET(fileno(fp), &set);
		FD_SET(sockfd, &set);
		max_fd = sockfd > fileno(fp) ? sockfd+1 : fileno(fp)+1;
		select(max_fd, &set, NULL, NULL, NULL);

		if (FD_ISSET(sockfd, &set))
		{
			if ((n = recv(sockfd, buff, 256, 0)) == 0){
				if (stdineof == 1)
					return ;
				else
				{
					printf("server err termi\n");
					exit(-1);
				}
			}
			write(fileno(stdout), buff, n);

		}

		if (FD_ISSET(fileno(fp), &set))
		{
			if ((n = read(fileno(fp), buff, 256)) == 0)
			{
				stdineof = 1;
				shutdown(sockfd, SHUT_WR);
				FD_CLR(fileno(fp), &set);

				continue;
			}

			send(sockfd, buff, n, 0);
		}
	}

}
int main(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_in s_addr;
  bzero(&s_addr, sizeof (s_addr));
  s_addr.sin_family = AF_INET;
  inet_pton(AF_INET, argv[1], &s_addr.sin_addr);
  s_addr.sin_port = htons(6666);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  connect(sockfd, (struct sockaddr *)&s_addr, sizeof (s_addr));
  
  str_cli_1(stdin, sockfd);

  exit(0);
}
