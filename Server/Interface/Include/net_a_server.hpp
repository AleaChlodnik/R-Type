/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netServer
*/

#pragma once

#include <net_i_server.hpp>

namespace r_type {
namespace net {
/**
 * @brief AServer class
 *
 * @tparam T
 */
template <typename T> class AServer : virtual public r_type::net::IServer<T> {
  public:
    /**
     * @brief Construct a new Server Interface object
     *
     * @param port
     */
    AServer(uint16_t port)
        : r_type::net::IServer<T>(),
          m_asioSocket(m_asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
    {
    }

    /**
     * @brief Destroy the Server Interface object
     *
     */
    ~AServer() { Stop(); }

    /**
     * @brief Start the server
     *
     * @return true
     * @return false
     */
    bool Start()
    {
        try {
            WaitForClientMessage();

            m_threadContext = std::thread([this]() { m_asioContext.run(); });
        } catch (std::exception &e) {
            std::cerr << "[SERVER] Exception: " << e.what() << std::endl;
            return false;
        }
        std::cout << "[SERVER] Started!" << std::endl;
        return true;
    }

    /**
     * @brief Stops the server.
     *
     * This function stops the server by stopping the ASIO context and joining the thread context.
     * It also prints a message indicating that the server has been stopped.
     */
    void Stop()
    {
        m_asioContext.stop();

        if (m_threadContext.joinable())
            m_threadContext.join();

        std::cout << "[SERVER] Stopped!\n";
    }

    /**
     * @brief Waits for a client message asynchronously.
     *
     * This function waits for a client message by asynchronously receiving data from the socket.
     * When a message is received, it checks if the client endpoint protocol is UDPv4.
     * If the protocol is not UDPv4, it recursively calls itself to wait for another client
     * message. If the protocol is UDPv4 and there are no errors, it prints the client endpoint and
     * checks if a connection already exists. If a connection already exists, it returns without
     * further processing. If a connection does not exist, it creates a new client socket, binds it
     * to a local endpoint, and creates a new connection object. It then calls the OnClientConnect
     * function to check if the client connection is approved. If the connection is approved, it
     * adds the new connection to the list of connections, connects it to the client, and prints
     * the connection ID. If the connection is denied, it prints a message indicating the
     * connection was denied. If there is an error during the receive operation, it prints the
     * error message.
     */
    void WaitForClientMessage()
    {
        m_asioSocket.async_receive_from(asio::buffer(m_tempBuffer.data(), m_tempBuffer.size()),
            m_clientEndpoint, [this](std::error_code ec, std::size_t bytes_recvd) {
                if (m_clientEndpoint.protocol() != asio::ip::udp::v4())
                    return WaitForClientMessage();
                if (!ec) {
                    std::cout << "[SERVER] New Connection: " << m_clientEndpoint << std::endl;
                    // check if connection already exists
                    for (std::shared_ptr<Connection<T>> &conn : m_deqConnections) {
                        if (conn->getEndpoint() == m_clientEndpoint) {
                            std::cout << "[SERVER] Connection already exists" << std::endl;
                            return;
                        }
                    }

                    asio::ip::udp::socket m_newSocket(
                        m_asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));

                    // create client socket
                    std::shared_ptr<Connection<T>> newConn = std::make_shared<Connection<T>>(
                        Connection<T>::owner::server, m_asioContext, std::move(m_newSocket),
                        m_clientEndpoint, m_qMessagesIn);

                    if (OnClientConnect(newConn)) {
                        m_deqConnections.push_back(std::move(newConn));
                        m_deqConnections.back()->ConnectToClient(this, nIDCounter++);
                        std::cout << "[" << m_deqConnections.back()->GetID()
                                  << "] Connection Approved" << std::endl;
                    } else {
                        std::cout << "[-----] Connection Denied" << std::endl;
                    }
                } else {
                    std::cout << "[SERVER] New Connection Error: " << ec.message() << std::endl;
                }
                m_clientEndpoint = asio::ip::udp::endpoint(asio::ip::udp::v4(), 0);
                WaitForClientMessage();
            });
    }

    /**
     * @brief send message message to client
     *
     * @param client
     * @param msg
     */
    void MessageClient(std::shared_ptr<Connection<T>> client, const Message<T> &msg)
    {
        if (client && client->IsConnected()) {
            client->Send(msg);
        } else {
            OnClientDisconnect(client);

            client.reset();

            m_deqConnections.erase(
                std::remove(m_deqConnections.begin(), m_deqConnections.end(), client),
                m_deqConnections.end());
        }
    }

    /**
     * @brief message all clients
     *
     * @param msg
     * @param pIgnoreClient
     */
    void MessageAllClients(
        const Message<T> &msg, std::shared_ptr<Connection<T>> pIgnoreClient = nullptr)
    {
        bool bInvalidClientExists = false;

        for (auto &client : m_deqConnections) {
            if (client && client->IsConnected()) {
                if (client != pIgnoreClient)
                    client->Send(msg);
            } else {
                OnClientDisconnect(client);
                client.reset();

                bInvalidClientExists = true;
            }
        }

        if (bInvalidClientExists)
            m_deqConnections.erase(
                std::remove(m_deqConnections.begin(), m_deqConnections.end(), nullptr),
                m_deqConnections.end());
    }

    /**
     * @brief update server
     *
     * @param nMaxMessages
     * @param bWait
     */
    void Update(size_t nMaxMessages = -1, bool bWait = false)
    {
        if (bWait)
            m_qMessagesIn.wait();

        size_t nMessageCount = 0;
        while (nMessageCount < nMaxMessages && !m_qMessagesIn.empty()) {
            auto msg = m_qMessagesIn.pop_front();

            OnMessage(msg.remote, msg.msg);

            nMessageCount++;
        }
    }

    virtual void OnClientValidated(std::shared_ptr<Connection<T>> client) {}

  protected:
    /**
     * @brief on client connect event
     *
     * @param client
     * @return true
     * @return false
     */
    virtual bool OnClientConnect(std::shared_ptr<Connection<T>> client) { return false; }

    /**
     * @brief on client disconnect event
     *
     * @param client
     */
    virtual void OnClientDisconnect(std::shared_ptr<Connection<T>> client) {}

    /**
     * @brief on message event
     *
     * @param client
     * @param msg
     */
    virtual void OnMessage(std::shared_ptr<Connection<T>> client, Message<T> &msg) {}

  public:
    ThreadSafeQueue<OwnedMessage<T>> m_qMessagesIn;

    std::deque<std::shared_ptr<Connection<T>>> m_deqConnections;

    asio::io_context m_asioContext;
    std::thread m_threadContext;

    asio::ip::udp::socket m_asioSocket;
    asio::ip::udp::endpoint m_clientEndpoint;

    std::array<uint8_t, 1024> m_tempBuffer;

    uint32_t nIDCounter = 10000;
};
} // namespace net
} // namespace r_type