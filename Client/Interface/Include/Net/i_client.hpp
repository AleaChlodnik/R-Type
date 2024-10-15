/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netClient
*/

#pragma once

#include <Net/common.hpp>
#include <Net/connection.hpp>
#include <Net/thread_safe_queue.hpp>

namespace r_type {
namespace net {
template <typename T> class IClient {
  public:
    IClient() {}

    virtual ~IClient() {}

  public:
    /**
     * @brief Connects to a remote host using UDP protocol.
     *
     * @param host The IP address or hostname of the remote host.
     * @param port The port number of the remote host.
     * @return true if the connection is successful
     * @return false otherwise.
     */
    virtual bool Connect(const std::string &host, const uint16_t port) = 0;

    /**
     * @brief Disconnects the client from the server.
     *
     * This function disconnects the client from the server if it is currently connected.
     * It stops the context and joins the context thread.
     * It also releases the connection resource.
     */
    virtual void Disconnect() = 0;

    /**
     * @brief Checks if the client is connected to the server.
     *
     * @return true
     * @return false
     */
    virtual bool IsConnected() = 0;

  public:
    /**
     * @brief Send message to server
     *
     * @param msg
     */
    virtual void Send(const Message<T> &msg) = 0;

    /**
     * @brief get incoming messages
     *
     * @return ThreadSafeQueue<OwnedMessage<T>>&
     */
    virtual ThreadSafeQueue<OwnedMessage<T>> &Incoming() = 0;
};
} // namespace net
} // namespace r_type