/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include "net_a_server.hpp"

namespace r_type {
namespace net {
class Server : virtual public r_type::net::AServer<NetR_TypeMessage> {
  public:
    Server(uint16_t nPort)
        : r_type::net::IServer<NetR_TypeMessage>(),
          r_type::net::AServer<NetR_TypeMessage>(nPort)
    {
    }

    ~Server() {}

  protected:
    virtual bool OnClientConnect(std::shared_ptr<r_type::net::Connection<NetR_TypeMessage>> client)
    {
        r_type::net::Message<NetR_TypeMessage> msg;
        msg.header.id = NetR_TypeMessage::ServerAccept;
        client->Send(msg);
        return true;
    }

    // Called when a client appears to have disconnected
    virtual void OnClientDisconnect(
        std::shared_ptr<r_type::net::Connection<NetR_TypeMessage>> client)
    {
        std::cout << "Removing client [" << client->GetID() << "]\n";
    }

    // Called when a message arrives
    virtual void OnMessage(std::shared_ptr<r_type::net::Connection<NetR_TypeMessage>> client,
        r_type::net::Message<NetR_TypeMessage> &msg)
    {
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
