#ifndef FILEUTIL_H_H
#define FILEUTIL_H_H

#include <boost/noncopyable.hpp>
#include "StringPiece.hpp"
#include <fcntl.h>

template<typename To, typename From>
inline To implicit_cast(From const& f)
{
	return f;
}

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





#endif /* FILEUTIL_H_H */
