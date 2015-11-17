#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

int main(void)
{
	int sd, con_sd;
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd <= 0)
	{
		printf("socket fd error");
		exit(-1);
	}

	struct sockaddr_in addr, c_addr;
	bzero(&addr, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(13);
	if (bind(sd, (struct sockaddr *)&addr, sizeof (addr)) < 0)
	{
		printf("bind error \n");
		exit(-1);
	}

	char *ptr;
	int backlog = 5;
	if ((ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);
	if (listen(sd, backlog) < 0)
	{
		printf("listen error \n");
		exit(-1);
	}
	
	socklen_t len;
	char buf[124];
	time_t ticks;
	while (1)
	{
		bzero(&c_addr, sizeof (struct sockaddr_in));
		con_sd = accept(sd, (struct sockaddr *)&c_addr, &len);
		printf("connect from %s, port %d\n", inet_ntop(AF_INET, &c_addr.sin_addr, buf, sizeof (buf)), ntohs(c_addr.sin_port));

		ticks = time(NULL);
		snprintf(buf, sizeof (buf), "%.24s\r\n", ctime(&ticks));
		write(con_sd, buf,strlen(buf));
		close(con_sd);
	}

	return 0;
}
