#ifndef BUFFER_H_H
#define BUFFER_H_H

#include <vector>
#include <assert.h>
#include <algorithm>
#include <string>
#include <string.h>
#include "Endian.h"
//#include <stdint.h>

class Buffer
{
public:
	static const size_t kCheapPrepend = 8;
	static const size_t kInitialSize = 1024;

	explicit Buffer(size_t initialSize = kInitialSize)
		: buffer_(kCheapPrepend + initialSize),
		  readerIndex_(kCheapPrepend),
		  writerIndex_(kCheapPrepend)
	{
		assert(readableBytes() == 0);
		assert(writableBytes() == initialSize);
		assert(prependableBytes() == kCheapPrepend);
	}

	void swap(Buffer& rhs)
	{
		buffer_.swap(rhs.buffer_);
		std::swap(readerIndex_, rhs.readerIndex_);
		std::swap(writerIndex_, rhs.writerIndex_);
	}
	
	size_t readableBytes() const
	{ return writerIndex_ - readerIndex_; }

	size_t writableBytes() const
	{ return buffer_.size() - writerIndex_; }

	size_t prependableBytes() const
	{ return readerIndex_; }

	const char* peek() const
	{ return begin() + readerIndex_; }

	const char* beginWrite() const
	{ return begin() + writerIndex_; }

	const char* findCRLF() const
	{
		const char* crlf = std::search(peek(), beginWrite(), kCRLF, kCRLF+2);
		return crlf == beginWrite() ? 0 : crlf;
	}

	const char* findCRLF(const char* start) const
	{
		assert(peek() <= start);
		assert(start <= beginWrite());

		const char* crlf = std::search(start, beginWrite(), kCRLF, kCRLF+2);
		return crlf == beginWrite() ? 0 : crlf;
	}

	const char* findEOL() const
	{
		const void* eol = memchr(peek(), '\n', readableBytes());
		return static_cast<const char*>(eol);
	}

	void retrieve(size_t len)
	{
		assert(len <= readableBytes());
		if (len < readableBytes())
		{
			readerIndex_ += len;
		}
		else
		{
			retrieveAll();
		}
	}

	void retrieveUnitl(const char* end)
	{
		assert(peek() <= end);
		assert(end <= beginWrite());
		retrieve(end - peek());
	}

	void retrieveInt64()
	{
		retrieve(sizeof (int64_t));
	}

	void retrieveInt32()
	{
		retrieve(sizeof (int32_t));
	}

	void retrieveInt16()
	{
		retrieve(sizeof (int16_t));
	}

	void retrieveInt8()
	{
		retrieve(sizeof (int8_t));
	}

	void retrieveAll()
	{
		readerIndex_ = kCheapPrepend;
		writerIndex_ = kCheapPrepend;
	}

	std::string retrieveAllAsString()
	{
		return retrieveAsString(readableBytes());
	}

	std::string retrieveAsString(size_t len)
	{
		assert(len <= readableBytes());
		std::string result(peek(), len);
		retrieve(len);
		return result;
	}
	
/*	StringPiece toStringPiece() const
	{
		return StringPiece(peek(), static_cast<int>(readableBytes()));
	}*/

	void append(const char* data, size_t length)
	{
		ensureWritableBytes(length);
		std::copy(data, data+length, begin() + writerIndex_);
		hasWritten(length);
	}

	void append(const void* data, size_t len)
	{
		append(static_cast<const char *>(data), len);
	}

	void ensureWritableBytes(size_t len)
	{
		if (writableBytes() < len)
		{
			makeSpace(len);
		}

		assert(writableBytes() >= len);
	}

	void hasWritten(size_t len)
	{
		assert(len < writableBytes());
		writerIndex_ += len;
	}

	void unwrite(size_t len)
	{
		assert(len < readableBytes());
		writerIndex_ -= len;
	}
	
	void appendInt64(int64_t x)
	{
		int64_t be64 = SocketOpt::hostToNetwork64(x);
		append(&be64, sizeof be64);
	}

	void appendInt32(int32_t x)
	{
		int32_t be32 = SocketOpt::hostToNetwork32(x);
		append(&be32, sizeof be32);
	}

	void appendInt16(int16_t x)
	{
		int16_t be16 = SocketOpt::hostToNetwork16(x);
		append(&be16, sizeof be16);
	}

	void appendInt8(int8_t x)
	{
		append(&x, sizeof x);
	}

	int64_t readInt64()
	{
		int64_t result = peekInt64();
		retrieveInt64();
		return result;
	}
	
	int32_t readInt32()
	{
		int32_t result = peekInt32();
		retrieveInt32();
		return result;
	}

	int16_t readInt16()
	{
		int16_t result = peekInt16();
		retrieveInt16();
		return result;
	}

	int8_t readInt8()
	{
		int8_t result = peekInt8();
		retrieveInt8();
		return result;
	}

	int64_t peekInt64()
	{
		assert(readableBytes() >= sizeof (int64_t));
		int64_t be64 = 0;
		memcpy(static_cast<void*>(&be64), peek(), sizeof be64);
		return SocketOpt::networkToHost64(be64);
	}

	int32_t peekInt32()
	{
		assert(readableBytes() >= sizeof (int32_t));
		int32_t be32 = 0;
		memcpy(&be32, peek(), sizeof be32);
		return SocketOpt::networkToHost32(be32);
	}

	int16_t peekInt16()
	{
		assert(readableBytes() >= sizeof (int16_t));
		int16_t be16 = 0;
		memcpy(&be16, peek(), sizeof be16);
		return SocketOpt::networkToHost16(be16);
	}

	int8_t peekInt8()
	{
		assert(readableBytes() >= sizeof (int8_t));
		int8_t x = *peek();
		return x;
	}
	
	void prependInt8(int8_t x)
	{
		prepend(&x, sizeof x);
	}

	void prependInt16(int16_t x)
	{
		int16_t be16 = SocketOpt::hostToNetwork16(x);
		prepend(&be16, sizeof be16);
	}

	void prependInt32(int32_t x)
	{
		int32_t be32 = SocketOpt::hostToNetwork32(x);
		prepend(&be32, sizeof be32);
	}

	void prependInt64(int64_t x)
	{
		int64_t be64 = SocketOpt::hostToNetwork64(x);
		prepend(&be64, sizeof be64);
	}

	void prepend(const void* data, size_t len)
	{
		assert(prependableBytes() >= len);
		readerIndex_ -= len;
		const char* d = static_cast<const char*>(data);
		std::copy(d, d+len, begin() + readerIndex_);
	}

	ssize_t readFd(const int fd, int* saveErrno);
private:
	void makeSpace(size_t len)
	{
		if (writableBytes() + prependableBytes() < len + kCheapPrepend)
		{
			buffer_.resize(writerIndex_ + len);
		}
		else
		{
			assert(kCheapPrepend < readerIndex_);
			size_t readable = readableBytes();

			std::copy(begin()+readerIndex_, 
					  begin()+writerIndex_,
					  begin()+kCheapPrepend);

			readerIndex_ = kCheapPrepend;
			writerIndex_ = readerIndex_ + readable;
			assert(readable == readableBytes());
		}
	}

	char* begin()
	{
		return &(*buffer_.begin());
	}

	const char* begin() const
	{ return &(*buffer_.begin()); }

private:
	std::vector<char> buffer_;
	size_t readerIndex_;
	size_t writerIndex_;

	static const char kCRLF[];
};


#endif /* BUFFER_H_H */
