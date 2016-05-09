#include "BaseSocket.h"
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>

typedef boost::unorder_map<int, BaseSocket *> EventMap;
EventMap g_event_map;

void AddBaseSocket(BaseSocket *pSock)
{
	g_event_map.insert(std::make_pair(pSock->GetSocket(), pSock));
}

void RemoveBaseSocket(BaseSocket *pSock)
{
	g_event_map.erase(pSock->GetSocket());
}

BaseSocket *FindBaseSocket(SOCKET fd)
{
	EventMap::iterator iter = g_event_map.find(fd);
	if (iter != g_event_map.end())
	{
		return iter->second;
	}

	return NULL;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

BaseSocket::BaseSocket()
{
	m_state = SOCKET_STATE_IDLE;
	m_fd = 0;
}

BaseSocket::~BaseSocket()
{
	if (m_fd > 0 && m_state != SOCKET_STATE_CLOSING)
		close(m_fd);
}

void BaseSocket::_SetNonblock(SOCKET fd)
{
	int flag = fcntl(fd, F_GETFL, 0);

	if (fcntl(fd, F_GETFL, flag | O_NONBLOCK) < 0)
	{
		// -1 error
	}
}

void BaseSocket::_SetReuseAddr(SOCKET fd)
{
	int reuse = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof (reuse)) < 0)
	{
		// error
	}
}

void BaseSocket::_SetNoDelay(SOCKET fd)
{
	int nodelay = 1;
	if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *)&nodelay, sizeof (nodelay)) < 0)
	{
		// error
	}
}

void BaseSocket::_SetAddr(const char *server_ip, uint16_t server_port, sockaddr_in* pAddr)
{
	pAddr->sin_family = AF_INET;
	pAddr->sin_port = htons(server_port);
//  pAddr->sin_addr.s_addr = inet_addr(server_ip);
	inet_pton(AF_INET, server_ip, &pAddr->sin_addr.s_addr);
	if (pAddr->sin_addr.s_addr == 0)
	{
		hosten *hten = gethostbyname(server_ip);
		if (hten == NULL)
		{
			return ;
		}

		pAddr->sin_addr.s_addr = *(uint32_t *)hten->h_addr;
	}

}

int BaseSocket::Listen(const char *server_ip, uint16_t server_port)
{
	local_ip = std::string(server_ip);
	local_port = server_port;

	m_fd = socket(AF_INET, SOCK_STREAM, 0);
	_SetReuseAddr(m_fd);
	_SetNoblock(m_fd);

	sockaddr_in srv_addr;
	bzero(&srv_addr, sizeof (sockaddr_in));
	_SetAddr(server_ip, server_port, &srv_addr);

	if (bind(m_fd, (sockaddr *)&srv_addr, sizeof (sockaddr_in)) < 0)
	{
		// error
		close(m_fd);
		return 0;
	}

	listen(m_fd, 64);
	m_state = SOCKET_STATE_LISTENING;
	EVENTDISPATCH->AddEvent(m_fd, EventDispatch::EVENT_READ);
	return 0;
}

int BaseSocket::Connect(const char *server_ip, uint16_t server_port)
{
	remote_ip = std::string(server_ip);
	remote_port = server_port;
	
	m_fd = socket(AF_INET, SOCK_STREAM, 0);
	_SetNoblock(m_fd);
	_SetNoDelay(m_fd);

	sockaddr_in srv_addr;
	bzero(&srv_addr, sizeof (sockaddr_in));
	_SetAddr(server_ip, server_port, &srv_addr);

	if (connect(m_fd, (sockaddr *)&srv_addr, sizeof (sockaddr_in)) < 0)
	{
		close(m_fd);
		return 0;
	}

	m_state = SOCKET_STATE_CONNECTING;
	AddBaseSocket(this);
	EVENTDISPATCH->AddEvent(m_fd, EventDispatch::EVENT_ALL);
	return 0;
}

int BaseSocket::Recv(char *buff, int size)
{
	return ::recv(m_fd, buff, size, 0);
}

int BaseSocket::Send(char *buff, int size)
{
	if (m_state != SOCKET_STATE_CONNECTING)
		return -1;

	int ret = send(m_fd, buff, size, 0);
	if (ret == -1)
	{
		//error
	}

	return ret;
}

int BaseSocket::Close()
{
	EVENTDISPATCH->RemoveEvent(m_fd);
	RemoveBaseSocket(this);
	close(m_fd);
	ReleaseRef();
}

int BaseSocket::_AcceptNewSocket()
{
	if (m_state != SOCKET_STATE_LISTENING)
	{
		//error
		return -1;
	}

	sockaddr_in cli_addr;
	socklen_t length;
	int fd;
	char ip_str[64];
	while ((fd = accept(m_fd, &cli_addr, &length)) > 0)
	{
		BaseSocket *pSock = new BaseSocket();
		uint32_t ip = ntohl(cli_addr.sin_addr.s_addr);
		uint16_t port = ntohs(cli_addr.sin_port);

		snprintf(ip_str, sizeof (ip_str), "%d.%d.%d.%d", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);

		pSock->SetRemoteIp(ip_str);
		pSock->SetSocket(fd);
		pSock->SetState(SOCKET_STATE_CONNECTED);
		pSock->SetRemotePort(port);
//		pSock->m_fd = fd;
//		pSock->m_state = SOCKET_STATE_CONNECTED;
//		pSock->remote_ip = local_ip;
//		pSock->remote_port = local_port;
		_SetNoblock(fd);
		_SetNoDelay(fd);

		AddBaseSocket(pSock);
		EVENTDISPATCH->AddEvent(m_fd, EventDispatch::EVENT_ALL);
	}
	
	return 0;
}

void BaseSocket::OnRead(void)
{
	if (m_state == SOCKET_STATE_LISTENING)
	{
		_AcceptNewSocket();
	}
	else
	{
		
	}
}

void BaseSocket::OnWrite(void)
{
	if (m_state == SOCKET_STATE_CONNECTING)
	{
		int error = 0;
		socklen_t len = sizeof (error);
		getsockopt(m_fd, SOL_SOCKET, SO_ERROR, (void *)&error, len);
		
		if (error)
		{
			//error
		}
		else
		{
			m_state = SOCKET_STATE_CONNECTED;
			//TODO:do something
		}
	}
	else
	{
		//TODO: do something
	}
}

void BaseSocket::OnClose()
{
	m_state = SOCKET_STATE_CLOSING;

}


