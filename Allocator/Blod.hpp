#include <vector>
#include <memory>
#include <new>
#include <string>
#include <algorithm>

template <typename T>
class Blod
{
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;

public:
	Blod();
	Blod(std::initializer_list<T> i);

	template <typename It> Blod(It b, It e);

	size_type size() const { return _data->size(); }
	bool empty() const { return _data->empty(); }

	void push_back(const T& t) { return _data->push_back(t); }
	void push_back(T&& t) { return _data->push_back(t); }

	void pop_back() { return _data->pop_back(); }
	T& back();
	T& operator[](size_type i);
private:
	void check(size_type i, const std::string& msg) const;

private:
	std::shared_ptr<std::vector<T>> _data;
};

template <typename T>
Blod<T>::Blod()
	: _data(new (std::nothrow) std::vector<T>) //FIXME::new throw is a bad error, better is crash
{

}

template <typename T>
Blod<T>::Blod(std::initializer_list<T> i)
	: _data(new std::vector<T> (i))
{

}

template <typename T>
T& Blod<T>::back()
{
	check(0, "back error");
	return _data->back();
}

template <typename T>
void Blod<T>::check(size_type i, const std::string& msg) const
{
	if (size() <= i)
		throw std::out_of_range(msg);
}

template <typename T>
T& Blod<T>::operator[](size_type i)
{
//    std::string str("operator [] error!");
	check(i, "error index");
	return (*_data)[i];
}

template <typename T>
template <typename It> Blod<T>::Blod(It b, It e)
	: _data(std::make_shared<std::vector<T>>())
{
	std::for_each(b, e, [this] (T& t) { push_back(t); });
}
