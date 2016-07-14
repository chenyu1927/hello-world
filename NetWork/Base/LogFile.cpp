#include "LogFile.h"
#include "FileUtil.h"
#include <assert.h>
#include <time.h>

LogFile::LogFile(const string& basename, size_t rollSize, bool threadSafe,
		int flushInterval, int checkEveryN)
	: basename_(basename),
	  rollSize_(rollSize),
	  flushInterval_(flushInterval),
	  checkEveryN_(checkEveryN),
	  count_(0),
	  mutex_(threadSafe ? new MutexLock() : 0),
	  startOfPeriod_(0),
	  lastRoll_(0),
	  lastFlush_(0)
{
	assert(basename.find('/') == string::npos);
	rollFile();
}

LogFile::~LogFile()
{

}

void LogFile::append(const char* logline, int len)
{
	if (mutex_)
	{
		MUTEX_GUARD(obj, *mutex_);
		append_unlocked(logline, len);
	}
	else
	{
		append_unlocked(logline, len);
	}
}

void LogFile::flush()
{
	if (mutex_)
	{
		MUTEX_GUARD(obj, *mutex_);
		file_->flush();
	}
	else
	{
		file_->flush();
	}
}

void LogFile::append_unlocked(const char* logline, int len)
{
	file_->append(logline, len);
	if (file_->writtenBytes() > rollSize_)
	{
		rollFile();
	}
	else
	{
		++ count_;
		if (count_ >= checkEveryN_)
		{
			count_ = 0;
			time_t now = ::time(0);
			time_t thisPeriod = now / kRollPerSeconds_ * kRollPerSeconds_;
			if (thisPeriod != startOfPeriod_)
			{
				rollFile();
			}
			else if (now - lastFlush_ > flushInterval_)
			{
				lastFlush_ = now;
				file_->flush();
			}
		}
	}
}

bool LogFile::rollFile()
{
	time_t now = 0;
	string filename = getLogFileName(basename_, &now);
	time_t start = now / kRollPerSeconds_ * kRollPerSeconds_;

	if (now > lastRoll_)
	{
		lastRoll_ = now;
		lastFlush_ = now;
		startOfPeriod_ = start;
		file_.reset(new AppendFile(filename));
		return true;
	}

	return false;
}

string LogFile::getLogFileName(const string& basename, time_t* now)
{
	string filename;
	filename.reserve(basename.size() + 64);
	filename = basename;

	char timebuf[32];
	struct tm tm;
	*now = time(NULL);
	localtime_r(now, &tm);
	strftime(timebuf, sizeof timebuf, ".%Y%m%d-%H%M%S", &tm);
	filename += timebuf;
/*
 * pid pid_name
 */
	filename += ".log";
	return filename;
}
