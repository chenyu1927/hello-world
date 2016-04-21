#ifndef EVENT_DISPATCH_H_H
#define EVENT_DISPATCH_H_H

#include <boost/noncopyable.hpp>

class EventDispatch : boost::noncopyable
{
public:
	enum {
		EVENT_READ = 0x1,
		EVENT_WRITE = 0x2,
		EVENT_ALL = 0x4
	};

	EventDispatch();
	~EventDispatch();

public:
	int addEvent(socket_t sockfd, uint8_t event);
	int removeEvent(socket_t sockfd, uint8_t event);

	void loop();
	void quit();

private:

	bool running_;
	int efd_;
};











#endif /* EVENT_DISPATCH_H_H */
