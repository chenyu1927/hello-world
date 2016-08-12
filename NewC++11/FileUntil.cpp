#include "FileUntil.h"
#include "Type.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string>
#include <assert.h>
#include <stdio.h>

fileUntil::ReadSmallFile::ReadSmallFile(StringArg filename)
	: fd_(::open(filename.c_str(), O_RDONLY | O_CLOEXEC)),
	  err_(0)
{
	buf_[0] = '\0';

	if (fd_ < 0)
		err_ = errno;
}

fileUntil::ReadSmallFile::~ReadSmallFile()
{
	if (fd_ >= 0)
		::close(fd_);
}

int fileUntil::ReadSmallFile::readToBuffer(int* size)
{
	int err = err_;
	if (fd_ >= 0)
	{
		ssize_t n = ::pread(fd_, buf_, sizeof(buf_)-1, 0);
		if (n >= 0)
		{
			if (n > 0)
				*size = static_cast<int>(n);
			buf_[n] = '\0';
		}
		else
			err = errno;
	}
	
	return err;
}

template <typename String>
int fileUntil::ReadSmallFile::readToString(int maxSize, String* context,
		int64_t* fileSize, int64_t* createTime, int64_t* modifyTime)
{
	static_assert(sizeof (off_t) == 8, "system diff");
	assert(context != nullptr);
	int err = err_;
	if (fd_ >= 0)
	{
		struct stat st_buf;	
		if (fstat(fd_, &st_buf) < 0)
			err_ = errno;
		else
		{
			context->clear();
			if (fileSize)
			{
				if (S_ISREG(st_buf.st_mode)) //regular file ==> normal file
				{
					*fileSize = st_buf.st_size;
					context->reserve(static_cast<int>(std::min(implicit_cast<int64_t>(maxSize), *fileSize)));
				}
				else if (S_ISDIR(st_buf.st_mode))
				{
					err = EISDIR;
				}

				if (createTime)
				{
					*createTime = st_buf.st_ctime;
				}

				if (modifyTime)
				{
					*modifyTime = st_buf.st_mtime;
				}
			}
		}

		while (context->size() < implicit_cast<size_t>(maxSize))
		{
			size_t toRead = static_cast<size_t>(std::min(implicit_cast<int64_t>(maxSize) - context->size()
						, sizeof buf_));
			ssize_t n = ::read(fd_, buf_, toRead);
			if (n > 0)
			{
				context->append(buf_, n);
			}
			else
			{
				if (n < 0)
					err = errno;
				break;
			}
		}
	}

	return err;
}

template int fileUntil::readFile(StringArg filename, int maxSize, std::string*, int64_t*, int64_t*, int64_t* );


fileUntil::AppendFile::AppendFile(StringArg filename)
	: fp_(::fopen(filename.c_str(), "a+")),
	  writtenBytes_(0)
{
	assert(fp_);
	::setbuffer(fp_, buffer_, sizeof buffer_);
}

fileUntil::AppendFile::~AppendFile()
{
	::fclose(fp_);
}

void fileUntil::AppendFile::flush()
{
	::fflush(fp_);
}

void fileUntil::AppendFile::Append(const char* log, const size_t len)
{
	size_t n = write(log, len);
	size_t remain = len - n;
	while (remain > 0)
	{
		size_t x = write(log+n, remain);
		if (x <= 0)
		{
			int err = ferror(fp_);
			if (err)
				fprintf(stderr, "AppendFile::Append() failed %s\n", strerror(err));
			break;
		}

		n += x;
		remain -= x;
	}

	writtenBytes_ += n;
}


size_t fileUntil::AppendFile::write(const char* log, const size_t len)
{
	return ::fwrite_unlocked(log, 1, len, fp_);
}
