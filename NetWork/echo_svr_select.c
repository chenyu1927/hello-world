#include<unistd.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<arpa/inet.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/select.h>


void str_echo(int sockfd)
{
  char buff[256];
  size_t n;

 again:
  while ((n = read(sockfd, buff, 255)) > 0)
  {
    write(sockfd, buff, n);
  }
  if (n < 0 && errno == EINTR)
  {
    goto again;
  }
  else if (n < 0)
    printf("read error\n");
}

void str_echo_1(int sockfd)
{
	int x, y;
	ssize_t n;
	char buff[256] = {0};
	for (; ;)
	{
		if ((n = read(sockfd, buff, 255)) <= 0)
				return ;
		if (sscanf(buff, "%d%d", &x, &y) == 2)
			snprintf(buff, sizeof (buff), "%d\n", x+y);
		else
			snprintf(buff, sizeof (buff), "input error\n");

		n = strlen(buff);
		write(sockfd, buff, n);
	}
}

void sig_handler(int sig)
{
	if (sig == SIGCHLD)
	{
		pid_t pid;
		int stat;
		pid = wait(&stat);     //存在信号压缩造成僵尸进程
		printf("child %d termial\n", pid);
	}
	return ;
}

void sig_handler2(int sig)
{
	pid_t pid;
	int stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0) // 循环会检测所有子进程
		printf("child %d terminal\n", pid);

	return ;
}

int main(void)
{
  int listenfd, cli_fd[FD_SETSIZE], sockfd, connfd;
  int maxfd, i, maxi, n;
  fd_set rset, allset;
  socklen_t client_len;
  char buff[256] = {0};
  struct sockaddr_in svr_addr, cli_addr;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd <= 0)
  {
    printf("socket error \n");
    return -1;
  }

  bzero(&svr_addr, sizeof (struct sockaddr_in));
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_port = htons(6666);
  svr_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(listenfd, (struct sockaddr *)&svr_addr, sizeof (struct sockaddr_in));
  listen(listenfd, 5);

  maxfd = listenfd;
  maxi = -1;
  for (i = 0; i < FD_SETSIZE; ++i)
  {
    cli_fd[i] = -1;
  }
  FD_ZERO(&allset);
  FD_SET(listenfd, &allset);
  while (1){
    rset = allset;
    select(maxfd, &allset, NULL, NULL, NULL);
    if (FD_ISSET(listenfd, &allset)){
      connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &client_len);
      for (i = 0; i < FD_SETSIZE; ++i)
      {
	if (cli_fd[i] < 0)
	{
	  cli_fd = connfd;
	  break;
	}
      }

      if (i == FD_SETSIZE)
      {
	printf("too many clients\n");
	return -1;
      }

      if (i > maxi)
	maxi = i;
    }

    for (i = 0; i < maxi; ++i)
    {
      if ((sockfd = cli_fd[i]) < 0)
	continue;
      if (FD_ISSET(sockfd, &allset))
      {
	if ((n = read(sockfd, buff, 255)) <= 0)
	{
	  close(sockfd);
	  FD_CLR(sockfd, &allset)
	  cli_fd[i] = -1;
	}
	else
	  write(sockfd, buff, n);
      }
    }
  }

  return 0;
}
