#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS

#endif 

#include "Timestamp.h"
#include <inttypes.h>
#include <sys/time.h>
#include <stdio.h>
#include <boost/static_assert.hpp>

BOOST_STATIC_ASSERT(sizeof (Timestamp) == sizeof (int64_t));

Timestamp Timestamp::now()
{
	struct timeval tv;
	::gettimeofday(&tv, NULL);
//	int64_t microSeconds = static_cast<int64_t>(tv.tv_sec * Timestamp::kMicroSecondsPerSecond + tv.tv_usec);
	int64_t sec = tv.tv_sec;
	return Timestamp(sec * Timestamp::kMicroSecondsPerSecond + tv.tv_usec);
}

std::string Timestamp::toString() const
{
	char buf[32] = {0};
	int seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
	int microSeconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;

	snprintf(buf, sizeof(buf) - 1, "%" PRId64 ".%06" PRId64 "", seconds, microSeconds);
	return buf;
}

std::string Timestamp::toFormattedString() const
{
	char buf[32] = {0};
	time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
	struct tm tm_time;
	gmtime_r(&seconds, &tm_time);

	snprintf(buf, sizeof (buf), "%4d-%02d-%02d %02d:%02d:%02d", 
			 tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
			 tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);

	return buf;
}

