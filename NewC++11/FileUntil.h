#ifndef FILE_UNTIL_H_H
#define FILE_UNTIL_H_H

#include <boost/noncopyable.hpp>
//#include <string>
#include "StringPiece.h"

namespace fileUntil
{
	// read small file < 64k
class ReadSmallFile : boost::noncopyable
{
public:
	ReadSmallFile(StringArg filename);
	~ReadSmallFile();

	template <typename String>
	int readToString(int maxSize, String* context, 
			int64_t* fileSize, int64_t* createTime, int64_t* modifyTime);

	int readToBuffer(int* size); //return err

	const char* buffer() const { return buf_; }

	static const int kBufferSize = 64 * 1024;
private:
	int fd_;
	int err_;
	char buf_[kBufferSize];
};

template <typename String>
int readFile(StringArg filename, int maxSize, String* context, 
		int64_t* fileSize = nullptr, int64_t* createTime = nullptr, 
		int64_t* modifyTime = nullptr)
{
	ReadSmallFile reader(filename);
	return reader.readToString(maxSize, context, fileSize, createTime, modifyTime);
}


class AppendFile : boost::noncopyable
{
public:
	explicit AppendFile(StringArg filename);
	~AppendFile();

	void Append(const char* logline, const size_t len);
	void flush();

	size_t writtenBytes() const { return writtenBytes_; }

private:
	size_t write(const char* logline, const size_t len);

	FILE* fp_;
	char  buffer_[64*1024];
	size_t writtenBytes_;
};

}



























#endif /* FILE_UNTIL_H_H */
