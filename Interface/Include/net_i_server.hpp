/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netServer
*/

#pragma once

#include "net_common.hpp"
#include "net_connection.hpp"
#include "net_message.hpp"
#include "net_thread_safe_queue.hpp"

namespace r_type {
namespace net {
/**
 * @brief IServer class
 *
 * @tparam T
 */
template <typename T> class IServer {
  public:
    /**
     * @brief Construct a new Server Interface object
     *
     * @param port
     */
    IServer(){};

    /**
     * @brief Destroy the Server Interface object
     *
     */
    virtual ~IServer(){};
    /**
     * @brief Start the server
     *
     * @return true
     * @return false
     */
    virtual bool Start() = 0;

    /**
     * @brief Stop the server
     *
     */
    virtual void Stop() = 0;

    /**
     * @brief wait for client connection
     *
     */
    virtual void WaitForClientMessage() = 0;

    /**
     * @brief send message message to client
     *
     * @param client
     * @param msg
     */
    virtual void MessageClient(std::shared_ptr<Connection<T>> client, const Message<T> &msg) = 0;

    /**
     * @brief message all clients
     *
     * @param msg
     * @param pIgnoreClient
     */
    virtual void MessageAllClients(
        const Message<T> &msg, std::shared_ptr<Connection<T>> pIgnoreClient = nullptr) = 0;

    /**
     * @brief update server
     *
     * @param nMaxMessages
     * @param bWait
     */
    virtual void Update(size_t nMaxMessages = -1, bool bWait = false) = 0;

    virtual void OnClientValidated(std::shared_ptr<Connection<T>> client) = 0;

  protected:
    /**
     * @brief on client connect event
     *
     * @param client
     * @return true
     * @return false
     */
    virtual bool OnClientConnect(std::shared_ptr<Connection<T>> client) = 0;

    /**
     * @brief on client disconnect event
     *
     * @param client
     */
    virtual void OnClientDisconnect(std::shared_ptr<Connection<T>> client) = 0;

    /**
     * @brief on message event
     *
     * @param client
     * @param msg
     */
    virtual void OnMessage(std::shared_ptr<Connection<T>> client, Message<T> &msg) = 0;
};
} // namespace net
} // namespace r_type