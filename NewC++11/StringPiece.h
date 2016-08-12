#ifndef STRING_PIECE_H_H
#define STRING_PIECE_H_H

#include <string>
#include <iosfwd>
#include <string.h>

class StringArg
{
public:
	StringArg(const char* str)
		: str_(str)
	{}

	StringArg(const std::string& str)
		: str_(str.c_str())
	{}

	const char* c_str() { return str_; }

private:
	const char* str_;
};


class StringPiece
{
public:
	StringPiece()
		: ptr_(nullptr), length_(0)
	{}

	StringPiece(const char* str)
		: ptr_(str), length_(static_cast<int>(strlen(ptr_)))
	{}

	StringPiece(const std::string& str)
		: ptr_(str.c_str()), length_(static_cast<int>(str.size()))
	{}

	StringPiece(const unsigned char* str)
		: ptr_(reinterpret_cast<const char*>(str)), 
		  length_(static_cast<int>(strlen(ptr_)))
	{}

	const char* ptr() const { return ptr_; }
	int size() const { return length_; }
	bool empty() const { return length_ == 0; }
	const char* begin() const { return ptr_; }
	const char* end() const { return ptr_ + length_; }

	void clear() { ptr_ = nullptr; length_ = 0; }
	void set(const char* buf, int length)
	{
		ptr_ = buf;
		length_ = length;
	}

	void set(const char* str)
	{
		ptr_ = str;
		length_ = static_cast<int>(strlen(str));
	}

	void set(const void* buf, int length)
	{
		ptr_ = reinterpret_cast<const char*>(buf);
		length_ = length;
	}

	char operator[](int i) const { return ptr_[i]; }

	void remove_prefix(int n)
	{
		ptr_ += n;
		length_ -= n;
	}

	void remove_suffix(int n)
	{
		length_ -= n;
	}

	bool operator==(const StringPiece& other)
	{
		return (length_ == other.length_) &&
			(memcmp(ptr_, other.ptr_, length_) == 0);
	}

	bool operator!= (const StringPiece& other)
	{
		return !(*this == other);
	}

	std::string as_string()
	{
		return std::string(ptr_, length_);
	}

	void copyToString(std::string* target)
	{
		target->assign(ptr_, length_);
	}

private:
	const char* ptr_;
	int			length_;
};

std::ostream& operator<<(std::ostream& o, const StringPiece& str);








#endif /* STRING_PIECE_H_H */
