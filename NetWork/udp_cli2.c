#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void dg_cli(FILE *fp, int sockfd, struct sockaddr *psrvaddr, socklen_t srvlen)
{
  int n;
  char sendmsg[256] = {0}, recvmsg[257] = {0};
  while (fgets(sendmsg, 256, fp) != NULL)
  {
    sendto(sockfd, sendmsg, strlen(sendmsg), 0, psrvaddr, srvlen);
//	send(sockfd, sendmsg, strlen(sendmsg), 0);
    n = recvfrom(sockfd, recvmsg, 256, 0, NULL, NULL);
    recvmsg[n] = 0;
    fputs(recvmsg, stdout);
	bzero(sendmsg, 256);
  }
}

int main(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_in srvaddr;
  bzero(&srvaddr, sizeof(srvaddr));
  srvaddr.sin_family = AF_INET;
  srvaddr.sin_port = htons(6666);
  inet_pton(AF_INET, "127.0.0.1", &srvaddr.sin_addr);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  //  bind(sockfd, (struct sockaddr*)&srvaddr, sizeof (srvaddr));
  connect(sockfd, (struct sockaddr*)&srvaddr, sizeof (struct sockaddr_in));

  dg_cli(stdin, sockfd, (struct sockaddr*)&srvaddr, sizeof (srvaddr));
  return 0;
}
