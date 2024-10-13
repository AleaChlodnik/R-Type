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
    virtual bool OnClientConnect(std::shared_ptr<r_type::net::Connection<TypeMessage>> client)
    {
        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::ServerAccept;

        asio::ip::udp::socket newSocket(
            m_asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));
        std::cout << "new socket:" << newSocket << std::endl;

        uint16_t newPort = newSocket.local_endpoint().port();

        msg << newPort;

        client->Send(msg);

        // // Close the current socket
        // m_asioSocket.close();

        // // Reinitialize m_asioSocket with the original port
        // m_asioSocket.open(asio::ip::udp::v4());
        // // m_asioSocket.bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), port));

        // std::cout << "Reinitialized socket on port: " << port << std::endl;

        // client.get()->setSocket(std::move(newSocket));
        std::shared_ptr<Connection<TypeMessage>> TMPConn =
            std::make_shared<Connection<TypeMessage>>(Connection<TypeMessage>::owner::server,
                m_asioContext, std::move(newSocket), m_clientEndpoint, m_qMessagesIn);

        client.reset();
        client = TMPConn;

        return true;
    }

    /**
     * @brief Called when a client appears to have disconnected
     *
     * @param client
     */
    virtual void OnClientDisconnect(std::shared_ptr<r_type::net::Connection<TypeMessage>> client)
    {
        std::cout << "Removing client [" << client->GetID() << "]\n";
    }

    /**
     * @brief Called when a message is received from a client
     *
     * @param client
     * @param msg
     */
    virtual void OnMessage(std::shared_ptr<r_type::net::Connection<TypeMessage>> client,
        r_type::net::Message<TypeMessage> &msg)
    {
        switch (msg.header.id) {
        case TypeMessage::ServerAccept: {
            std::cout << "[" << client->GetID() << "]: Server Accept" << std::endl;

        } break;
        case TypeMessage::ServerDeny: {

        } break;
        case TypeMessage::ServerPing: {
            std::cout << "[" << client->GetID() << "]: Server Ping" << std::endl;

            // Simply bounce message back to client
            client->Send(msg);
        } break;

        case TypeMessage::MessageAll: {
            std::cout << "[" << client->GetID() << "]: Message All" << std::endl;

            // Construct a new message and send it to all clients
            r_type::net::Message<TypeMessage> msg;
            msg.header.id = TypeMessage::ServerMessage;
            msg << client->GetID();
            MessageAllClients(msg, client);

        } break;
        case TypeMessage::ClientConnect: {
            std::cout << "[" << client->GetID() << "]: Client Connect" << std::endl;
        } break;
        case TypeMessage::ServerMessage: {
        } break;
        case TypeMessage::CreateEntityMessage: {
        } break;
        case TypeMessage::CreateEntityResponse: {
        } break;
        case TypeMessage::DestroyEntityMessage: {
        } break;
        case TypeMessage::DestroyEntityResponse: {
        } break;
        case TypeMessage::MoveEntityMessage: {
        } break;
        }
    }
};
} // namespace net
} // namespace r_type
