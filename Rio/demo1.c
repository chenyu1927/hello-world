#include<unistd.h>
#include<stdio.h>

int rio_readn(int fd, void *usrbuf, size_t n)
{
	size_t nleft = n;
	int nread;
	char *bufp = usrbuf;
	while(nleft > 0)
	{
		if ((nread = read(fd, bufp, nleft)) < 0)
		{
			if (errno == EINTR)   //interrupted by sig handler
				nread = 0;
			else
				return -1;
		}
		else if (nread == 0)    // eof
			break;

		nleft -= nread;
		bufp += nread;
	}

	return (n - nleft);
}

int rio_writen(int fd, void *usrbuf, size_t n)
{
	size_t nleft = n;
	int nwrite;
	char *bufp = usrbuf;
	
	while (nleft > 0)
	{
		if ((nwrite = write(fd, bufp, nleft)) <= 0)
		{
			if (errno == EINTR)
				nwrite = 0;
			else
				return -1;
		}
		nleft -= nwrite;
		bufp += nwrite;
		}
	}
	
	return (n - nleft);
}
