#pragma once
#include "netCommon.hpp"
#include "netThreadSafeQueue.hpp"
#include "netMessage.hpp"

namespace olc {
namespace net {
template <T>
class connection: public std::enable_shared_from_this<connection<T>> {
public:
    connection() {}
    virtual ~connection() {}
public:
    bool ConnectToServer();
    bool Disconnect();
    bool IsConnected() const;
public:
    bool Send(const message<T>& msg);
protected:
    asio::ip::tcp::socket m_socket;

    asio::io_context& m_asioContext;

    ThreadSafeQueue<message<T>> m_qMessagesOut;

    ThreadSafeQueue<owned_message>& m_qMessagesIn;
}

}
}
