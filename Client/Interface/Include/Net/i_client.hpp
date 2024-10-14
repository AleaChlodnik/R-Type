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
     * @brief Connect to server
     *
     * @param host
     * @param port
     * @return true
     * @return false
     */
    virtual bool Connect(const std::string &host, const uint16_t port) = 0;

    /**
     * @brief Disconnect from server
     *
     */
    virtual void Disconnect() = 0;

    /**
     * @brief return status of connection
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