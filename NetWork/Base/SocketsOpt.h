#ifndef SOCKETSOPT_H_H
#define SOCKETSOPT_H_H

#include <arpa/inet.h>

namespace socketopt
{
	int createNonblockingOrDie(sa_family_t family);

	int connect(int sockfd, const struct sockaddr* addr);
	void bindOrDie(int sockfd, const struct sockaddr* addr);
	void listenOrDie(int sockfd);
}






#endif /* SOCKETSOPT_H_H */
