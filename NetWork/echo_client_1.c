#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>

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
int main(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_in s_addr;
  bzero(&s_addr, sizeof (s_addr));

  s_addr.sin_family = AF_INET;
  inet_pton(AF_INET, "127.0.0.1", &s_addr.sin_addr);
  s_addr.sin_port = htons(6666);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

//  int flag = fcntl(sockfd, F_GETFL, 0);
  //fcntl(sockfd, F_SETFL, flag | O_NONBLOCK);

  connect(sockfd, (struct sockaddr *)&s_addr, sizeof (s_addr));
  
  str_cli(stdin, sockfd);

  exit(0);
}
