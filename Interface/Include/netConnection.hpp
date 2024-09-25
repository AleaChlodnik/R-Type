#pragma once
#include "netCommon.hpp"
#include "netMessage.hpp"
#include "netThreadSafeQueue.hpp"

namespace olc {
namespace net {
template <typename T>
class connection : public std::enable_shared_from_this<connection<T>> {
  public:
    enum class owner
    {
        server,
        client
    };

  public:
    connection(owner parent, asio::io_context &asioContext,
        asio::ip::tcp::socket socket, ThreadSafeQueue<owned_message<T>> &qIn)
        : m_asioContext(asioContext), m_socket(std::move(socket)),
          m_qMessagesIn(qIn)
    {
        m_nOwnerType = parent;
    }

    virtual ~connection() {}

    uint32_t GetID() const { return id; }

  public:
    bool ConnectToServer();
    bool Disconnect();
    bool IsConnected() const;

  public:
    bool Send(const message<T> &msg);

  protected:
    asio::ip::tcp::socket m_socket;

    asio::io_context &m_asioContext;

    ThreadSafeQueue<message<T>> m_qMessagesOut;

    ThreadSafeQueue<owned_message<T>> &m_qMessagesIn;

    message<T> m_msgTemporaryIn;

    owner m_nOwnerType = owner::server;

    uint32_t id = 0;
};

} // namespace net
} // namespace olc
