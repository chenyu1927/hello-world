#include<sys/socket.h>

int main(void)
{
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr;

}
