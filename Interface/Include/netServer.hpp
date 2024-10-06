/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netServer
*/

#pragma once

#include "netCommon.hpp"
#include "netConnection.hpp"
#include "netMessage.hpp"
#include "netThreadSafeQueue.hpp"

namespace olc {
namespace net {
/**
 * @brief ServerInterface class
 *
 * @tparam T
 */
template <typename T> class ServerInterface {
  public:
    /**
     * @brief Construct a new Server Interface object
     *
     * @param port
     */
    ServerInterface(uint16_t port)
        : m_asioSocket(m_asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
    {
    }

    /**
     * @brief Destroy the Server Interface object
     *
     */
    virtual ~ServerInterface() { Stop(); }
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
            std::cerr << "[SERVER] Exception: " << e.what() << "\n";
            return false;
        }

        std::cout << "[SERVER] Started!\n";
        return true;
    }

    /**
     * @brief Stop the server
     *
     */
    void Stop()
    {
        m_asioContext.stop();

        if (m_threadContext.joinable())
            m_threadContext.join();

        std::cout << "[SERVER] Stopped!\n";
    }

    /**
     * @brief wait for client connection
     *
     */
    void WaitForClientMessage()
    {
        m_asioSocket.async_receive_from(asio::buffer(m_tempBuffer.data(), m_tempBuffer.size()),
            m_clientEndpoint, [this](std::error_code ec, std::size_t bytes_recvd) {
                if (!ec && bytes_recvd > 0) {
                    std::cout << "[SERVER] Received message from "
                              << m_clientEndpoint << "\n";

                    // // Handle the received message here, e.g., push to a message queue
                    // Message<T> msg;
                    // // Deserialize message from buffer
                    // OnMessage(m_clientEndpoint, msg);

                    // Wait for the next client message
                    WaitForClientMessage();
                } else {
                    std::cout << "[SERVER] Receive Error: " << ec.message() << "\n";
                }
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

  protected:
    ThreadSafeQueue<OwnedMessage<T>> m_qMessagesIn;

    std::deque<std::shared_ptr<Connection<T>>> m_deqConnections;

    asio::io_context m_asioContext;
    std::thread m_threadContext;

    asio::ip::udp::socket m_asioSocket;
    asio::ip::udp::endpoint m_clientEndpoint;
    // std::shared_ptr<olc::net::Connection<T>> m_clientEndpoint;
    std::array<uint8_t, 1024> m_tempBuffer;

    uint32_t nIDCounter = 10000;
};
} // namespace net
} // namespace olc