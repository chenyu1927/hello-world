#include<unistd.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include<errno.h>
#include<sys/wait.h>
#define MAXLINE 256
void str_echo(int sockfd)
{
  char buff[MAXLINE];
  size_t n;
  while (1)
  {
    if ((n = read(sockfd, buff, MAXLINE-1)) < 0)
    {
      if (errno == EINTR)
	continue;
      else
	return ;
    }
    write(sockfd, buff, n);
  }
}

int max(int a, int b)
{
  return a > b ? a : b;
}

int main(int argc, char **argv)
{
  int listenfd, connfd, udpfd, nready, maxfdpl;
  char mesg[MAXLINE];
  pid_t child;
  fd_set rset;
  ssize_t n;
  socklen_t len;
  const int on = 1;
  struct sockaddr_in cliaddr, svraddr;
  void sig_chld(int);

  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&svraddr, sizeof (svraddr));
  svraddr.sin_family = AF_INET;
  svraddr.sin_port = htons(0);
  svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (on));
  bind(listenfd, (struct sockaddr *)&svraddr, sizeof (svraddr));
  listen(listenfd, 5);

  udpfd = socket(AF_INET, SOCK_DGRAM, 0);
  bzero(&cliaddr, sizeof (cliaddr));
  cliaddr.sin_family = AF_INET;
  cliaddr.sin_port = htons(0);
  cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  bind(udpfd, (struct sockaddr *)&cliaddr, sizeof (cliaddr));

  signal(SIGCHLD, sig_chld);
  FD_ZERO(&rset);
  maxfdpl = max(listenfd, udpfd) + 1;
  while (1)
  {
    FD_SET(listenfd, &rset);
    FD_SET(udpfd, &rset);
    if ((nready = select(maxfdpl, &rset, NULL, NULL, NULL)) < 0)
    {
      if (errno == EINTR)
	continue;
      else
	return -1;
    }

    if (FD_ISSET(listenfd, &rset))
    {
      len = sizeof (cliaddr);
      connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);

      if ((child = fork()) ==  0)
      {
	close(listenfd);
	str_echo(connfd);
	exit(0);
      }

      close(connfd);
    }

    if (FD_ISSET(udpfd, &rset))
    {
      len = sizeof (cliaddr);
      n = recvfrom(udpfd, mesg, MAXLINE, 0, (struct sockaddr*)&cliaddr, &len);
      sendto(udpfd, mesg, n, 0, (struct sockaddr *)&cliaddr, len);
    }
  }

  return 0;
}

void sig_chld(int sig)
{
  if (sig == SIGCHLD)
  {
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
      printf("child %d terminal !", pid);
    }
  }
}
