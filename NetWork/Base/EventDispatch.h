#ifndef EVENT_DISPATCH_H_H
#define EVENT_DISPATCH_H_H

#include <boost/noncopyable.hpp>
#include "Singleton.hpp"
#include <stdint.h>

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
	int AddEvent(int sockfd, uint8_t event);
	int RemoveEvent(int sockfd, uint8_t event = 0);

	void Loop();
	void Quit();

private:

	bool running_;
	int efd_;
};

typedef Singleton<EventDispatch> EventDispatchSingle;
#define EVENTDISPATCH EventDispatchSingle::instance()


#endif /* EVENT_DISPATCH_H_H */
