#include "InetAddress.h"
#include "SocketsOpt.h"

InetAddress::InetAddress(StringArg ip, uint16_t port)
{
	::bzero(&addr_, sizeof addr_);

	socketopt::fromIpPort(ip.c_str(), port, &addr_);
}

std::string InetAddress::toIp() const
{
	char buf[64] = " ";
//	int32_t ip = ::ntohl(addr_.sin_addr.s_addr);
//	snprintf(buf, sizeof buf, "%d.%d.%d.%d", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
	::inet_ntop(AF_INET, static_cast<const void *>(&addr_.sin_addr), buf, static_cast<socklen_t>(sizeof addr_));
	return buf;
}

uint16_t toPort() const
{
	return ::ntohs(addr_.sin_port);
}

const struct sockaddr* InetAddress::getSockAddr() const
{
	return static_cast<const struct sockaddr*>(implicit_cast<const void*>(&addr_));
}

static __thread char t_resolveBuffer[64 * 1024];
bool InetAddress::resolve(StringArg hostname, InetAddress* result)
{
	assert(result != 0);
	struct hostent hent;
	struct hostent* he = 0;
	int herrno = 0;
	bzero(&hent, sizeof hent);

	int ret = gethostbyname_r(hostname.c_str(), &hent, t_resolveBuffer, sizeof t_resolveBuffer, &he, &herrno);
	if (ret == 0 && he != 0)
	{
		assert(he->h_addrtype == AF_INET && he->h_length == sizeof (uint32_t));
		out->addr_.sin_addr = *reinterpret_cast<struct in_addr*>(he->h_addr);
		return true;
	}
	else
	{
		if (ret)
		{
			// FIXME:log

		}

		return false;
	}
}
