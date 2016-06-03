#ifndef INETADDRESS_H_H
#define INETADDRESS_H_H

#include "StringPiece.hpp"

class InetAddress
{
public:
	explicit InetAddress(StringArg ip, uint16_t port);
	
	explicit InetAddress(const struct sockaddr_in& addr)
		: addr_(addr)
	{ }

	InetAddress()
	{
		::memset(&addr_, 0, sizeof addr_);
	}

	sa_family_t family() const { return addr_.sin_family; }

	std::string toIp() const;
	std::string toIpPort() const;
	uint16_t toPort() const;

	const struct sockaddr* getSockAddr() const;

	uint32_t ipNetEndian() const;
	uint16_t portNetEndian() const { return addr_.port; }

	static bool resolve(StringArg hostname, InetAddress* result);

private:
/*	union{
		struct sockaddr_in addr;
		struct sockaddr_in6 addr6;
	}*/
	struct sockaddr_in addr_;
};






#endif /* INETADDRESS_H_H */
