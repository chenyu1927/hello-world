#include "FileUtil.h"
#include <boost/static_assert.hpp>
#include <unistd.h>
//#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <assert.h>

ReadSmallFile::ReadSmallFile(StringArg filename)
	  : err_(0)
{
	buf_[0] = '\0';
	fd_ = ::open(filename.c_str(), O_RDWR);
	if (fd_ < 0)
	{
		//error
		err_ = errno;
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
