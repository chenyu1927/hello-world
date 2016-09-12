#ifndef HTTP_CONTENT_H_H
#define HTTP_CONTENT_H_H

#include "HttpRequest.h"
#include "Timestamp.h"

class Buffer;

class HttpContext
{
public:
	enum HttpRequestParseState
	{
		kExpectRequestLine,
		kExpectHeaders,
		kExpectBody,
		kGetAll
	};

	HttpContext()
		: state_(kExpectRequestLine)
	{}

	bool parseRequest(Buffer* buf, Timestamp receiveTime);

	bool getAll() const { return state_ == kGetAll; }

	void reset()
	{
		state_ = kExpectRequestLine;
		HttpRequest dummp;
		dummp.swap(request_);
	}

	const HttpRequest& request() const
	{ return request_; }

	HttpRequest& request()
	{ return request_; }

private:
	bool processRequestLine(const char* begin, const char* end);

	HttpRequestParseState state_;
	HttpRequest request_;
};















#endif //HTTP_CONTENT_H_H
