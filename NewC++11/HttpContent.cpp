#include "HttpContent.h"
#include "Buffer.h"

bool HttpContext::parseRequest(Buffer* buff, Timestamp time)
{
	bool ok = true;
	bool hasMore = true;
	while (hasMore)
	{
		if (state_ == kExpectRequestLine)
		{
			const char* crlf = buff->findCRLF();
			if (crlf)
			{
				ok = processRequestLine(buff->peek(), crlf);
				if (ok)
				{
					request_.setReceiveTime(time);
					buff->retrieveUnitl(crlf+2);
					state_ = kExpectHeaders;
				}
				else
				{
					hasMore = false;
				}
			}
			else
			{
				hasMore = false;
			}
		}
		else if (state_ == kExpectHeaders)
		{
			const char* crlf = buff->findCRLF();
			if (crlf)
			{
				const char* colon = std::find(buff->peek(), crlf, ':');
				if (colon != crlf)
				{
					request_.addHeader(buff->peek(), colon, crlf);
				}
				else
				{
					state_ = kGetAll;
					hasMore = false;
				}

				buff->retrieveUnitl(crlf+2);
			}
			else
			{
				hasMore = false;
			}
		}
		else if (state_ == kExpectBody)
		{
			
		}
	}

	return ok;
}

bool HttpContext::processRequestLine(const char* begin, const char* end)
{
	bool succeed = false;
	const char* start = begin;
	const char* space = std::find(begin, end, ' ');
	if (space != end && request_.setMethod(start, space))
	{
		start = space + 1;
		const char* space = std::find(start, end, ' ');
		if (space != end)
		{
			const char* question = std::find(start, space, '?');
			if (question != space)
			{
				request_.setPath(start, question);
				request_.setQuery(question, space);
			}
			else
			{
				request_.setPath(start, space);
			}
	
			start = space + 1;
			succeed = end-start == 8 && std::equal(start, end-1, "HTTP1.");
			if (succeed)
			{
				if (*(end-1) == '1')
				{
					request_.setVersion(HttpRequest::kHttp11);
				}
				else if (*(end-1) == '0')
				{
					request_.setVersion(HttpRequest::kHttp10);
				}
				else
				{
					succeed = false;
				}
			}
		}
	}

	return succeed;
}
