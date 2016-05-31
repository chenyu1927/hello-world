#include "FileUtil.h"
#include <boost/static_assert.hpp>
#include <unistd.h>
//#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdio.h>


ReadSmallFile::ReadSmallFile(StringArg filename)
	  : err_(0)
{
	buf_[0] = '\0';
	fd_ = ::open(filename.c_str(), O_RDWR);
	if (fd_ < 0)
	{
		//error
		err_ = errno;
		abort();
	}

}

ReadSmallFile::~ReadSmallFile()
{
	if (fd_ >= 0)
		::close(fd_);
}

template<typename String>
int ReadSmallFile::readToString(int maxSize,
								String *content,
								int64_t *fileSize,
								int64_t *modifyTime,
								int64_t *createTime)
{
	BOOST_STATIC_ASSERT(sizeof (off_t) == 8); /*struct stat 中的off_t */
	assert(content != 0);

	int err = err_;
	if (fd_ >= 0)
	{
		content->clear();
		if (fileSize)
		{
			struct stat statbuf;
			if (::fstat(fd_, &statbuf))
			{
				if (S_ISREG(statbuf.st_mode)) //常规文件
				{
					*fileSize = statbuf.st_size;
					content->reserve(static_cast<int>(std::min(implicit_cast<int64_t>(maxSize), *fileSize)));
				}
				else if (S_ISDIR(statbuf.st_mode)) //目录
				{
					err = EISDIR;
				}

				if (modifyTime)
				{
					*modifyTime = statbuf.st_mtime;
				}

				if (createTime)
				{
					*createTime = statbuf.st_ctime;
				}
			}
			else
			{
				err = errno;
			}
		}
		
		while (content.size() < implicit_cast<size_t>(maxSize))
		{
			size_t toRead = std::min(implicit_cast<size_t>(maxSize) - content.size(), sizeof (buf_));
			ssize_t n = ::read(fd_, buf_, toRead);
			if (n > 0)
			{
				content.append(buf_, n);
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

int ReadSmallFile::readToBuffer(int *size)
{
	int err = err_;
	if (fd_ >= 0)
	{
		ssize_t n = ::pread(fd_, buf_, sizeof(buf_)-1, 0);
		if (n > 0)
		{
			if (size)
				*size = implicit_cast<int> (n);
			buf_[n] = '\0';
		}
		else
		{
			err = errno;
		}
	}
	return err;
}

/* *************************************************************************** */
char t_errnobuf[512];
const char* strerror_tl(int savedError)
{
	return ::strerror_r(savedError, t_errnobuf, sizeof (t_errnobuf));
}

/* *************************************************************************** */

AppendFile::AppendFile(StringArg filename)
	: fp_(::fopen(filename.c_str(), "ae")),
	  writtenBytes_(0)
{
	assert(fp_);
	::setbuffer(fp_, buf_, sizeof (buf_));
}

AppendFile::~AppendFile()
{
	if (fp_)
		fclose(fp_);
}

void AppendFile::append(const char* logline, const size_t len)
{
	size_t n = write(logline, len);
	size_t remain = len - n;
	while (remain > 0)
	{
		size_t x = write(logline + n, remain);
		if (x == 0)
		{
			int err = ferror(fp_);
			if (err)
			{
				fprintf(stderr, "AppendFile::append() failed %s\n", strerror_tl(err));
			}
			break;
		}

		n += x;
		remain = len - n;
	}

	writtenBytes_ += len;
}

size_t AppendFile::write(const char* logline, const size_t len)
{
	return ::fwrite_unlocked(logline, 1, len, fp_);
}

void AppendFile::flush()
{
	::fflush(fp_);
}
