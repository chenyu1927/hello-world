#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/epoll.h>
#include<stdlib.h>
#include<errno.h>
#include<arpa/inet.h>

#define MAXEVENTS 10
//如何将这种网络通用编程和逻辑分离开来是Reactor的本质

void set_socket_nonblocking(int sd)
{
	int flag;
	flag = fcntl(sd, F_GETFL, 0);
	if (flag != -1)
	{
		flag |= O_NONBLOCK;
		if (fcntl(sd, F_SETFL, flag) == -1)
		{
			perror("set socket nonblock error");
		}
	}
}

//如何正确的读取ET模式下的nonblock fd
//如果返回0，表示end of file
//EAGAIN表示fd变成不可读的状态
int handle_recv(int fd, char *buff, int size)
{
	int n = 0;
	int nread;
	while ((nread = read(fd, buff + n, size - 1)) > 0){
		n += nread;
	}

	if (nread == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
	{
		//出错
		perror("read error");
		return -1;
	}

	return n;
}

int handle_send(int fd, char *buff, int n)
{
	int data_size = n;
	int nwrite;
	while (n > 0){
		nwrite = write(fd, buff + data_size - n, n);
		if (nwrite == -1 && errno != EAGAIN)
		{
			perror("write error");
			return -1;
		}

		n -= nwrite;
	}

	return n;
}

//ET模式下的nonblock fd accept要注意两个问题
//如果客户端在accept之前关掉了连接，会返回-1，并设置errno为EPROTO或者ECONNABORTED
//需要处理所有的连接 返回-1 或者 EAGAIN结束

int handle_accept(int fd)
{
	int conn_sock;
	while ((conn_sock = accept(fd, NULL, NULL)) > 0){
		
	}

	if (conn_sock == -1)
	{
		if (errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO 
				&& errno != EINTR){
			perror("accept error");
			return -1;
		}
	}
	
	return 0;
}

int create_listen_sock(char *port)
{
	int listen_sock;
	struct sockaddr_in s_addr;
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(6666);
	inet_pton(AF_INET, "127.0.0.1", &s_addr.sin_addr);

	if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("create socket error");
		return -1;
	}
//	bind(listen_sock, (struct sockaddr *)&s_addr, sizeof (struct sockaddr_in));
	return listen_sock;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
//		fprintf(stderr, "Usage: %s [port]", argv[0]);
//		return 0;
	}

	int listen_sd, epoll_sd, conn_sd, err, n;
	struct epoll_event event;
	struct epoll_event events[MAXEVENTS];
	struct sockaddr_in remote, s_addr;
	socklen_t addr_l;
	char buff[BUFSIZ];

	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(6666);
	inet_pton(AF_INET, "127.0.0.1", &s_addr.sin_addr);
	listen_sd = socket(AF_INET, SOCK_STREAM, 0);
//	listen_sd = create_listen_sock(argv[1]);
	if (listen_sd < 0)
	{
		return 0;
	}

	set_socket_nonblocking(listen_sd);
	bind(listen_sd, (struct sockaddr *)&s_addr, sizeof (struct sockaddr_in));
	listen(listen_sd, 100);

	epoll_sd = epoll_create(10);
	if (epoll_sd < 0)
	{
		perror("epoll create error");
		return 0;
	}

	event.data.fd = listen_sd;
	event.events = EPOLLIN | EPOLLET;

	err = epoll_ctl(epoll_sd, EPOLL_CTL_ADD, listen_sd, &event);
	if (err == -1)
	{
		perror("epoll ctl error");
		return 0;
	}

	int i;
	while (1)
	{
		n = epoll_wait(epoll_sd, events, MAXEVENTS, -1);
		if (n == -1)
		{
			perror("epoll wait error");
			exit(-1);
		}
		
		int fd;
		int nread;
		int nwrite;
		for (i = 0; i < n; ++i)
		{
			fd = events[i].data.fd;
			if (fd == listen_sd)
			{
				while ((conn_sd = accept(listen_sd, (struct sockaddr *)&remote, &addr_l)) > 0)
				{
					if (conn_sd == -1)
					{
						if (errno != EAGAIN && errno != EINTR)
						{
							perror("accept");
						}
					}
					else if (conn_sd > 0)
					{
						set_socket_nonblocking(conn_sd);
						event.data.fd = conn_sd;
						event.events = EPOLLIN | EPOLLET;
						err = epoll_ctl(epoll_sd, EPOLL_CTL_ADD, conn_sd, &event);
						if (err == -1)
						{
							perror("epoll ctl connfd error");
							exit(-1);
						}
					}
				}
				continue;
			}

			if(events[i].events & EPOLLIN)
			{
				n = 0;
				while ((nread = read(fd, buff+n, BUFSIZ-1)) > 0)
				{
					n += nread;
				}

				if (nread == -1 && errno == EAGAIN)
				{
					perror("can not read");
				}
				/*else if (n > 0)
				{
					event.data.fd = fd;
					event.events = EPOLLOUT | EPOLLET;
					epoll_ctl(epoll_sd, EPOLL_CTL_MOD, fd, &event);
				}*/

				int data_size = n;
				while (n > 0)
				{
					nwrite = write(fd, buff+ data_size - n, n);
					if (nwrite == -1 && errno == EAGAIN)
					{
						perror("can not write");
					}

					n -= nwrite;
				}
			}

			if (events[i].events & EPOLLOUT)
			{

				/*int data_size = n;
				while (n > 0)
				{
					nwrite = write(fd, buff+ data_size - n, n);
					if (nwrite == -1 && errno == EAGAIN)
					{
						perror("can not write");
					}

					n -= nwrite;
				}*/
			}
		}
		
	}

	return 0;
}

