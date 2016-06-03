#ifndef SOCKETSOPT_H_H
#define SOCKETSOPT_H_H

#include <arpa/inet.h>

namespace socketopt
{
	int createNonblockingOrDie(sa_family_t family);

	int connect(int sockfd, const struct sockaddr* addr);
	void bindOrDie(int sockfd, const struct sockaddr* addr);
	void listenOrDie(int sockfd);

	int accept(int sockfd, struct sockaddr_in* addr);
	ssize_t read(int sockfd, void* buf, size_t count);
	ssize_t write(int sockfd, void* buf, size_t count);
	void close(int sockfd);
	void shutdownWrite(int sockfd);
	
	void fromIpPort(const char* ip, uint16_t port, struct sockaddr_in* addr);


	int getSocketError(int sockfd);
	const struct sockaddr* sockaddr_cast(const struct sockaddr_in* addr);
	const struct sockaddr_in* sockaddr_in_cast(const struct sockaddr* addr);

	struct sockaddr_in getLocalAddr(int sockfd);
	struct sockaddr_in getPeerAddr(int sockfd);

	bool isSelfConnect(int sockfd);
}






#endif /* SOCKETSOPT_H_H */
