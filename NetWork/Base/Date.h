#ifndef DATE_H_H
#define DATE_H_H

#include <boost/noncopyable.hpp>
#include <sys/time.h>
#include <string>


class Date : boost::noncopyable
{
public:

	struct YearMonthDay
	{
		int year;
		int month;
		int day;
	};

	static const int kDaysPerWeek = 7;

	Date()
		: julianDayNumber_(0)
	{}

	Date(int year, int month, int day);

	explicit Date(int julianDayNumber)
		: julianDayNumber_(julianDayNumber)
	{}

	explicit Date(const struct tm&);

	void swap(Date& other)
	{
		std::swap(julianDayNumber_, other.julianDayNumber_);
	}

	bool valid() const { return julianDayNumber_ > 0; }

	std::string toIsoString() const;

	struct YearMonthDay yearMonthDay() const;

	int year() const
	{
		return yearMonthDay().year;
	}

	int month() const
	{
		return yearMonthDay().month;
	}

	int day() const
	{
		return yearMonthDay().day;
	}

	int weekDay() const
	{
		return (julianDayNumber_ + 1) % kDaysPerWeek;
	}

	int julianDayNumber() const { return julianDayNumber_; }

private:
	int julianDayNumber_;
};
























#endif /* DATE_H_H */
