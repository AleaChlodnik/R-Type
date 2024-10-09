/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#pragma once

#include "net_a_server.hpp"

namespace r_type {
namespace net {
class Server : virtual public r_type::net::AServer<NetR_TypeMessage> {
  public:
    Server(uint16_t nPort)
        : r_type::net::IServer<NetR_TypeMessage>(), r_type::net::AServer<NetR_TypeMessage>(nPort)
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
    virtual bool OnClientConnect(std::shared_ptr<r_type::net::Connection<NetR_TypeMessage>> client)
    {
        r_type::net::Message<NetR_TypeMessage> msg;
        msg.header.id = NetR_TypeMessage::ServerAccept;
        client->Send(msg);
        return true;
    }

    /**
     * @brief Called when a client appears to have disconnected
     *
     * @param client
     */
    virtual void OnClientDisconnect(
        std::shared_ptr<r_type::net::Connection<NetR_TypeMessage>> client)
    {
        std::cout << "Removing client [" << client->GetID() << "]\n";
    }

    /**
     * @brief Called when a message is received from a client
     *
     * @param client
     * @param msg
     */
    virtual void OnMessage(std::shared_ptr<r_type::net::Connection<NetR_TypeMessage>> client,
        r_type::net::Message<NetR_TypeMessage> &msg)
    {
        std::cout << "Received a message from [" << client->GetID() << "]" << std::endl;
        switch (msg.header.id) {
        case NetR_TypeMessage::ServerPing: {
            std::cout << "[" << client->GetID() << "]: Server Ping\n";

            // Simply bounce message back to client
            client->Send(msg);
        } break;

        case NetR_TypeMessage::MessageAll: {
            std::cout << "[" << client->GetID() << "]: Message All\n";

            // Construct a new message and send it to all clients
            r_type::net::Message<NetR_TypeMessage> msg;
            msg.header.id = NetR_TypeMessage::ServerMessage;
            msg << client->GetID();
            MessageAllClients(msg, client);

        } break;
        case NetR_TypeMessage::ClientConnect: {
            std::cout << "[" << client->GetID() << "]: Client Connect\n";
        } break;
        }
    }
};
} // namespace net
} // namespace r_type
