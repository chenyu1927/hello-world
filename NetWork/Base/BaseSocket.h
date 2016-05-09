#ifndef BASESOCKET_H_H
#define BASESOCKET_H_H

#include "RefObject.hpp"

typedef int SOCKET;
enum{

	SOCKET_STATE_IDLE,
	SOCKET_STATE_LISTENING,
	SOCKET_STATE_CONNECTING,
	SOCKET_STATE_CONNECTED,
	SOCKET_STATE_CLOSING
};

class BaseSocket : public RefObject
{
public:

	BaseSocket();
	virtual ~BaseSocket();

public:
	int Listen(
			const char* server_ip,
			uint16_t	server_port);
	int Connect(
			const char* server_ip,
			uint16_t	server_port
			);

public:
	int Recv(char *buff, int size);
	int Send(char *buff, int size);
	int Close();

public:
	void OnRead();
	void OnWrite();
	void OnClose();

private:

	void _SetNonblock(SOCKET fd);
	void _SetResuseAddr(SOCKET fd);
	void _SetNoDelay(SOCKET fd);

	void _SetAddr(const char *server_ip, uint16_t server_port, sockaddr_in* pAddr);
private:

	std::string remote_ip;
	uint16_t	remote_port;
	std::string local_ip;
	uint16_t	local_port;

	uint8_t m_state;
	SOCKET 	m_fd;

};

BaseSocket* FindBaseSocket(SOCKET fd);



#endif /* BASESOCKET_H_H */
