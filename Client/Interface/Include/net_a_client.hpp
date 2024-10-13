/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netClient
*/

#pragma once

#include "net_i_client.hpp"

namespace r_type {
namespace net {
template <typename T> class AClient : virtual public IClient<T> {
  public:
    AClient() {}

    virtual ~AClient() { Disconnect(); }

  public:
    /**
     * @brief Connect to server
     *
     * @param host
     * @param port
     * @return true
     * @return false
     */
    bool Connect(const std::string &host, const uint16_t port)
    {
        try {
            asio::ip::udp::resolver resolver(m_context);
            asio::ip::udp::resolver::results_type results_type_endpoints =
                resolver.resolve(host, std::to_string(port));

            asio::ip::udp::endpoint endpoint = *results_type_endpoints.begin();

            m_connection = std::make_unique<Connection<T>>(Connection<T>::owner::client, m_context,
                asio::ip::udp::socket(m_context), endpoint, m_qMessagesIn);
            m_connection->ConnectToServer(results_type_endpoints);

            thrContext = std::thread([this]() { m_context.run(); });
        } catch (std::exception &e) {
            std::cerr << "Client Exception: " << e.what() << std::endl;
            return false;
        }
        return true;
    }

    /**
     * @brief Disconnect from server
     *
     */
    void Disconnect()
    {
        if (IsConnected()) {
            m_connection->Disconnect();
        }

        m_context.stop();
        if (thrContext.joinable())
            thrContext.join();

        m_connection.release();
    }

    /**
     * @brief return status of connection
     *
     * @return true
     * @return false
     */
    bool IsConnected()
    {
        if (m_connection)
            return m_connection->IsConnected();
        else
            return false;
    }

  public:
    /**
     * @brief Send message to server
     *
     * @param msg
     */
    void Send(const Message<T> &msg)
    {
        if (IsConnected())
            m_connection->Send(msg);
    }

    /**
     * @brief get incoming messages
     *
     * @return ThreadSafeQueue<OwnedMessage<T>>&
     */
    ThreadSafeQueue<OwnedMessage<T>> &Incoming() { return m_qMessagesIn; }

    const std::unique_ptr<Connection<T>> &getConnection() { return m_connection; }

  protected:
    asio::io_context m_context;
    std::thread thrContext;
    std::unique_ptr<Connection<T>> m_connection;

  private:
    ThreadSafeQueue<OwnedMessage<T>> m_qMessagesIn;
};
} // namespace net
} // namespace r_type