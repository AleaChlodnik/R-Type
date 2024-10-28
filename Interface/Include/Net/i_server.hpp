/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netServer
*/

#pragma once

#include "common.hpp"
#include "connection.hpp"
#include "message.hpp"
#include "thread_safe_queue.hpp"
#include <entity_struct.hpp>
#include <cstdint>

namespace r_type {
namespace net {

/**
 * @class IServer
 * @brief Interface for a server.
 *
 * This class provides an interface for a server implementation.
 * It defines methods for starting and stopping the server, waiting for client connections,
 * sending messages to clients, updating the server, and handling client events.
 *
 * @tparam T The type of the connection.
 */
template <typename T> class IServer {
  public:
    /**
     * @brief Construct a new Server Interface object
     *
     * @param port
     */
    IServer() {};

    /**
     * @brief Destroy the Server Interface object
     *
     */
    virtual ~IServer() {};
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
     * @brief Sends a message to a client.
     *
     * This function is responsible for sending a message to a specific client.
     *
     * @param client A shared pointer to the client connection.
     * @param msg The message to be sent.
     */
    virtual void MessageClient(std::shared_ptr<Connection<T>> client, const Message<T> &msg) = 0;

    /**
     * @brief Sends a message to all clients connected to the server.
     *
     * @param msg The message to be sent.
     * @param pIgnoreClient An optional pointer to a client connection to ignore when sending the
     * message.
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

    /**
     * @brief Send all the existing entities to the client
     *
     * @param client
     * @param entity
     */
    virtual void InitListEntities(
        std::shared_ptr<r_type::net::Connection<T>> client, uint32_t entityID) = 0;

    virtual void OnClientValidated(std::shared_ptr<Connection<T>> client) = 0;

    /**
     * @brief Initiate players
     *
     * @param msg
     * @param clientId
     */

    virtual EntityInformation InitiatePlayers(int clientId) = 0;

    /**
     * @brief Remove player
     *
     * @param clientId
     */
    virtual void RemovePlayer(uint32_t id) = 0;

    /**
     * @brief Remove entities
     *
     * @param entityId
     */
    virtual void RemoveEntity(uint32_t id) = 0;

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