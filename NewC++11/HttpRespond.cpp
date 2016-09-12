#include "HttpRespond.h"
#include "Buffer.h"
#include <stdio.h>

void HttpRespond::appendToBuffer(Buffer* buffer) const
{
	char buf[32];
	snprintf(buf, sizeof buf, "HTTP1.1/ %d ", statusCode_);
	buffer->append(buf);
	buffer->append(statusMessage_);
	buffer->append("\r\n");

	if (closeConnection_)
	{
		buffer->append("Connection: Close\r\n");
	}
	else
	{
		snprintf(buf, sizeof buf, "Content-Length: %zd\r\n", body_.size());
		buffer->append(buf);
		buffer->append("Connection: Keep-Alive\r\n");
	}

	for (auto iter : headers_)
	{
		buffer->append(iter.first);
		buffer->append(": ");
		buffer->append(iter.second);
		buffer->append("\r\n");
	}

	buffer->append("\r\n");
	buffer->append(body_);

}
