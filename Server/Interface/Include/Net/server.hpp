/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#pragma once

#include <cstdint>
#include "a_server.hpp"

namespace r_type {
namespace net {
class Server : virtual public r_type::net::AServer<TypeMessage> {
  public:
    Server(uint16_t nPort)
        : r_type::net::IServer<TypeMessage>(), r_type::net::AServer<TypeMessage>(nPort)
    {
    }

    ~Server() {}

  protected:
    /**
     * @brief Called when a client is validated
     *
     * @param client
     * @return true
     * @return false
     */
    bool OnClientConnect(std::shared_ptr<r_type::net::Connection<TypeMessage>> client);

    /**
     * @brief Called when a client appears to have disconnected
     *
     * @param client
     */
    void OnClientDisconnect(std::shared_ptr<r_type::net::Connection<TypeMessage>> client,
        r_type::net::Message<TypeMessage> &msg);

    /**
     * @brief Called when a message is received from a client
     *
     * @param client
     * @param msg
     */
    void OnMessage(std::shared_ptr<r_type::net::Connection<TypeMessage>> client,
        r_type::net::Message<TypeMessage> &msg);

    /**
     * @brief Sends a list of existing entities to a newly connected client for initialization.
     *
     * The function iterates through all existing entities and sends their information to the
     * newly connected client, excluding specific entities such as the client itself.
     *
     * @param client The connection to the client.
     * @param entityID The ID of the entity to exclude (usually the client's own entity).
     */
    void InitListEntities(
        std::shared_ptr<r_type::net::Connection<TypeMessage>> client, uint32_t entityID);
};
} // namespace net
} // namespace r_type
