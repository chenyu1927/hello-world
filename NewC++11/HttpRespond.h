#ifndef HTTP_RESPOND_H_H
#define HTTP_RESPOND_H_H

#include <map>
#include <string>

class Buffer;

class HttpRespond
{
public:
	typedef std::map<std::string, std::string> Header;

	enum HttpStatusCode
	{
		kUnknown, 
		k200Ok = 200,
		k301MovedPermanently = 300,
		k400BadRequest = 400,
		k404NotFound = 404,
	};

	explicit HttpRespond(bool close)
		: statusCode_(kUnknown),
		  closeConnection_(close)
	{}

	void setStatusCode(HttpStatusCode statusCode)
	{ statusCode_ = statusCode; }

	void setStatusMessage(std::string&& statusMessage)
	{ statusMessage_ = statusMessage; }

	void setCloseConnection(bool close)
	{ closeConnection_ = close; }

	bool closeConnection() const { return closeConnection_; }

	void setContentType(std::string&& contentType)
	{ addHeader("content-type", contentType); }

	void addHeader(const std::string& key, const std::string& value)
	{ headers_[key] = value; }

	void setBody(std::string&& body)
	{ body_ = body; }

	void appendToBuffer(Buffer* buffer) const;


private:

	Header headers_;
	HttpStatusCode statusCode_;
	std::string statusMessage_;
	bool closeConnection_;
	std::string body_;
};





#endif //HTTP_RESPOND_H_H
