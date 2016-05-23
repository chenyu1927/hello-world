#ifndef BASESOCKET_H_H
#define BASESOCKET_H_H

#include "RefObject.h"
#include <stdint.h>
#include <arpa/inet.h>
#include <string>

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
	inline SOCKET GetSocket() {  return m_fd; }
	inline void SetRemoteIp(const char* str) { remote_ip = str; }
	inline void SetSocket(SOCKET fd) { m_fd = fd; }
	inline void SetState(uint16_t state) { m_state = state; }
	inline void SetRemotePort(uint16_t port) { remote_port = port; }
public:
	int Recv(char *buff, int size);
	int Send(char *buff, int size);
	int Close();

public:
	void OnRead();
	void OnWrite();
	void OnClose();

private:

	void _SetNoblock(SOCKET fd);
	void _SetReuseAddr(SOCKET fd);
	void _SetNoDelay(SOCKET fd);
	int  _AcceptNewSocket();
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
