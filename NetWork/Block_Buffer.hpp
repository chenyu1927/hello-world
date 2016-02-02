#include<vector>
#include<string>
#include<algorithm>

class Block_Buffer{
public:
  Block_Buffer(size_t init_size = 2084, size_t init_offset = 4 * sizeof (int));
  void reset();
  size_t readable_bytes()const;
  size_t writeable_bytes() const;
  size_t head_bytes()const;

  char *get_read_ptr();
  char *get_write_ptr();
  void ensure_writeable_bytes(size_t len);
  size_t make_space(size_t len);
  char * begin()
  {
	 return &* this->buffer_.begin();
  }
  void append()


private:
  size_t init_size_;
  size_t init_offset_;
  size_t read_index_, write_index_;
  std::vector<char> buffer_;
};

Block_Buffer::Block_Buffer(size_t init_size, size_t init_offset)
	:init_size_(init_size), init_offset_(init_offset), read_index_(init_offset),
	write_index_(init_offset)
{
	this->buffer_.clear();
}

size_t Block_Buffer::readable_bytes()
{
	return this->write_index_ - this->read_index_;
}

size_t Block_Buffer::writeable_bytes()
{
	return this->buffer_.size() - this->write_index_;
}

size_t Block_Buffer::pre_free_bytes()
{
	return this->read_index_;
}

size_t make_space(size_t len)
{
//	buffer_.resize(write_index_ + len);
	if (writeable_bytes() + pre_free_bytes() < init_offset_ + len)
	{
		buffer_.resize(write_index_ + len);
	}
	else
	{
		assert(init_offset_ < read_index_);
		size_t readable = readable_bytes();
		std::copy(begin()+read_index_,
				  begin()+write_index_,
				  begin()+size_offset_);
		read_index_ = init_offset_;
		write_index = read_index_ + readable;
		assert(readable == readable_bytes());
	}
}

void Block_Buffer::ensure_writeable_bytes(size_t len)
{
	if (this->writeable_bytes() < len)
	{
		make_space(len);
	}
	assert(this->writeable_bytes >= len);
}
