#ifndef FILEUTIL_H_H
#define FILEUTIL_H_H

#include <boost/noncopyable.hpp>
#include "StringPiece.hpp"
#include <fcntl.h>
#include <string.h>

template<typename To, typename From>
inline To implicit_cast(From const& f)
{
	return f;
}

/*char errbuf[512];  全局变量定义报错---全局变量不能定义在头文件*/

const char* strerror_tl(int savedErrno);
/*{
	return ::strerror_r(savedErrno, errbuf, sizeof (errbuf));
}*/

class ReadSmallFile : boost::noncopyable
{
public:
	ReadSmallFile(StringArg fileName);
	~ReadSmallFile();

	template<typename String>
	int readToString(int maxSize,
					 String *content,
					 int64_t *fileSize,
					 int64_t *modifyTime,
					 int64_t *createTime);

	int readToBuffer(int *size);

	inline const char* buffer() { return buf_; }

	static const int kBufferSize = 64*1024;
private:
	int fd_;
	int err_;
	char buf_[kBufferSize];
};

class AppendFile : boost::noncopyable
{
public:
	explicit AppendFile(StringArg filename);

	~AppendFile();

	void append(const char* logline, const size_t len);

	void flush();

	size_t writtenBytes() const { return writtenBytes_; }
private:
	
	size_t write(const char* logline, const size_t len);

	FILE *fp_;
	char buf_[64*1024];
	size_t writtenBytes_;
};



#endif /* FILEUTIL_H_H */
