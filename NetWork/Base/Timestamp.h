#ifndef TIME_STAMP_H_H
#define TIME_STAMP_H_H

//#include <inttype.h>
#include <algorithm>
#include <string>
class Timestamp 
{
public:

	Timestamp()
		: microSecondsSinceEpoch_(0)
	{

	}

	explicit Timestamp(int64_t microSeconds)
		: microSecondsSinceEpoch_(microSeconds)
	{

	}

	void swap(Timestamp& that)
	{
		std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
	}

	bool valid() { return microSecondsSinceEpoch_ > 0; }

	int64_t microSecondsSinceEpoch() { return microSecondsSinceEpoch_; }

	time_t secondsSinceEpoch() { return microSecondsSinceEpoch_ / kMicroSecondsPerSecond; }

	static Timestamp now();

	static Timestamp invalid()
	{
		return Timestamp();
	}

	static Timestamp fromUnixTime(time_t t)
	{
		return fromUnixTime(t, 0);
	}

	static Timestamp fromUnixTime(time_t t, int64_t microSeconds)
	{
		return Timestamp(static_cast<int64_t> (t * kMicroSecondsPerSecond) + microSeconds);
	}

	std::string toString() const;
	std::string toFormattedString() const;

	static const int kMicroSecondsPerSecond = 1000 * 1000;
private:
	int64_t microSecondsSinceEpoch_;
};

inline bool operator<(Timestamp lhs, Timestamp rhs)
{
	return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator==(Timestamp lhs, Timestamp rhs)
{
	return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

inline double timeDiffence(Timestamp high, Timestamp low)
{
	int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
	return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
}

inline Timestamp addTime(Timestamp timestamp, double seconds)
{
	int64_t microSeconds = static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
	return Timestamp(timestamp.microSecondsSinceEpoch() + microSeconds);
}



#endif /* TIME_STAMP_H_H */
