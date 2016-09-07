#ifndef TYPE_H_H
#define TYPE_H_H

#include <functional>
#include <memory>
#include "Timestamp.h"
template <typename To, typename From>
To implicit_cast(From f)
{
	return f;
}

class TcpConnection;
class Buffer;
typedef std::shared_ptr<TcpConnection>	TcpConnectionPtr;
typedef std::function<void (const TcpConnectionPtr&)> ConnectionCallback;
typedef std::function<void (const TcpConnectionPtr&)> CloseCallback;
typedef std::function<void (const TcpConnectionPtr&)> WriteCompleteCallback;
typedef std::function<void (const TcpConnectionPtr&, size_t)> HighWaterMarkCallback;


typedef std::function<void (const TcpConnectionPtr&,
							Buffer*, Timestamp)> MessageCallback;

void defaultConnectionCallback(const TcpConnectionPtr& conn);
void defaultMessageCallback(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp receiveTime);














#endif /* TYPE_H_H */
