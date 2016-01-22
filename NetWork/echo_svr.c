#include<unistd.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<arpa/inet.h>
#include<signal.h>
#include<sys/wait.h>
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
  signal(SIGCHLD, sig_handler2);
  int listen_fd, conn_fd;
  pid_t child;
  struct sockaddr_in addr, c_addr;
  socklen_t client;
  bzero(&addr, sizeof (addr));
  bzero(&c_addr, sizeof (addr));
  listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  addr.sin_family = AF_INET;
//  inet_pton(AF_INET, argv[1], &addr.sin_addr);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(6666);

  bind(listen_fd, (struct sockaddr *)&addr, sizeof (struct sockaddr_in));
  listen(listen_fd, 5);
  while (1)
  {
    conn_fd = accept(listen_fd, (struct sockaddr *)&c_addr, &client);
    if ((child = fork()) == 0)
    {
      close(listen_fd);
      str_echo(conn_fd);
      exit(-1);
    }

    close(conn_fd);
  }

  return 0;
}
