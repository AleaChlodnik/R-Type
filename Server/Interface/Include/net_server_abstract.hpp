/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netServer
*/

#pragma once

#include <net_server_interface.hpp>

namespace r_type {
namespace net {
/**
 * @brief NetServerAbstract class
 *
 * @tparam T
 */
template <typename T> class NetServerAbstract : virtual public r_type::net::NetServerInterface<T> {
  public:
    /**
     * @brief Construct a new Server Interface object
     *
     * @param port
     */
    NetServerAbstract(uint16_t port);

    /**
     * @brief Destroy the Server Interface object
     *
     */
    ~NetServerAbstract();
    /**
     * @brief Start the server
     *
     * @return true
     * @return false
     */
    bool Start();

    /**
     * @brief Stop the server
     *
     */
    void Stop();

    /**
     * @brief wait for client connection
     *
     */
    void WaitForClientMessage();

    /**
     * @brief send message message to client
     *
     * @param client
     * @param msg
     */
    void MessageClient(std::shared_ptr<Connection<T>> client, const Message<T> &msg);

    /**
     * @brief message all clients
     *
     * @param msg
     * @param pIgnoreClient
     */
    void MessageAllClients(
        const Message<T> &msg, std::shared_ptr<Connection<T>> pIgnoreClient = nullptr);

    /**
     * @brief update server
     *
     * @param nMaxMessages
     * @param bWait
     */
    void Update(size_t nMaxMessages = -1, bool bWait = false);

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
    using r_type::net::NetServerInterface<T>::m_qMessagesIn;
    using r_type::net::NetServerInterface<T>::m_deqConnections;
    using r_type::net::NetServerInterface<T>::m_asioContext;
    using r_type::net::NetServerInterface<T>::m_threadContext;
    using r_type::net::NetServerInterface<T>::m_asioSocket;
    using r_type::net::NetServerInterface<T>::m_clientEndpoint;
    using r_type::net::NetServerInterface<T>::m_tempBuffer;
    using r_type::net::NetServerInterface<T>::nIDCounter;
};
} // namespace net
} // namespace r_type