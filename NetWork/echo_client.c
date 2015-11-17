#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/select.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
void str_cli(FILE *fp, int sockfd)
{
  char sendline[256], recvline[256];
  bzero(sendline, 256);
  bzero(recvline, 256);
  while (fgets(sendline, 256, fp) != NULL)
  {
    send(sockfd, sendline, strlen(sendline), 0);
    if (recv(sockfd, recvline, 256, 0) == 0)
      return;
    fputs(recvline, stdout);
	bzero(sendline, 256);
	bzero(recvline, 256);
  }
}
void str_cli_1(FILE *fp, int sockfd)
{
  char sendline[256], recvline[256];
  fd_set rset;
  int maxfd;
  int n;
  bzero(sendline, 256);
  bzero(recvline, 256);
  FD_ZERO(&rset);
  while (1)
  {
    FD_SET(fileno(fp), &rset);
    FD_SET(sockfd, &rset);
    maxfd = MAX(fileno(fp), sockfd) +1;
    select(maxfd, &rset, NULL, NULL, NULL);
    if (FD_ISSET(sockfd, &rset))
    {
      n = recv(sockfd, recvline, 256, 0);
      if (n > 0)
      {
	fputs(recvline, stdout);
      }
    }
    if (FD_ISSET(fileno(fp), &rset))
    {
      if (fgets(sendline, 256, fp) != NULL)
	send(sockfd, sendline, strlen(sendline), 0);
    }
    bzero(sendline, 256);
    bzero(recvline, 256);
  }
}
int main(int argc, char **argv)
{
  int sockfd[5];
  struct sockaddr_in s_addr;
  bzero(&s_addr, sizeof (s_addr));
  s_addr.sin_family = AF_INET;
  inet_pton(AF_INET, argv[1], &s_addr.sin_addr);
  s_addr.sin_port = htons(6666);
  int i;
  for (i = 0; i < 5; ++i)
  {
	  sockfd[i] = socket(AF_INET, SOCK_STREAM, 0);
	  connect(sockfd[i], (struct sockaddr *)&s_addr, sizeof (s_addr));
  }
  str_cli_1(stdin, sockfd[0]);

  exit(0);
}
