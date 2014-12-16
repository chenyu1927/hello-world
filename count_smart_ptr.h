#ifndef COUNT_PTR_H_H
#define COUMT_PTR_H_H
template<class T>
class Count_ptr{
	private:
		T* ptr;
		long* count;

	public:

		explicit Count_ptr(T* p = 0) : ptr(p), count(new long(1)) {

		}

		Count_ptr (const Count_ptr<T>& other) throw()
			: ptr(other.ptr), count(other.count)
		{
			++*count;

		}

		Count_ptr& operator= (const Count_ptr<T>& other) throw()
		{
			if (this == &other)
			{
				return *this;
			}
			
			this->dispose();
			this->ptr = other.ptr;
			this->count = other.count;
			++*count;

			return *this;
		}

		T& operator* () const throw()
		{
			return *ptr;
		}
		
		T* operator-> () const throw()
		{
			return ptr;
		}

		long show_count()
		{
			return *count;
		}

	private:

		void dispose()
		{
			if (--*count == 0)
			{
				delete count;
				delete ptr;
				count = 0;
				ptr = 0;
			}
		}



};
#endif
