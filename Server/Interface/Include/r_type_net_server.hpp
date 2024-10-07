/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include "net_server_abstract.hpp"

class R_TypeNetServer : virtual public r_type::net::NetServerAbstract<NetR_TypeMessage> {
  public:
    R_TypeNetServer(uint16_t nPort)
        : r_type::net::NetServerAbstract<NetR_TypeMessage>(nPort),
          r_type::net::NetServerInterface<NetR_TypeMessage>(nPort)
    {
    }
    ~R_TypeNetServer() {}

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
