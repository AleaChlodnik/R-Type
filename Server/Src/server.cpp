/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <Net/server.hpp>

bool r_type::net::Server::OnClientConnect(
    std::shared_ptr<r_type::net::Connection<TypeMessage>> client)
{
    r_type::net::Message<TypeMessage> msg;
    EntityInformation entity;
    msg.header.id = TypeMessage::ServerAccept;
    InitiatePlayers(msg);
    nbr_of_player++;
    MessageClient(client, msg);
    msg.header.id = TypeMessage::CreateEntityMessage;
    MessageAllClients(msg, client);
    msg >> entity;
    InitListEntities(client, entity);
    return true;
}

/**
 * @brief Called when a client appears to have disconnected
 *
 * @param client
 */
void r_type::net::Server::OnClientDisconnect(
    std::shared_ptr<r_type::net::Connection<TypeMessage>> client,
    r_type::net::Message<TypeMessage> &msg)
{
    int entityId;
    std::cout << "[" << client->GetID() << "]: Removing client" << std::endl;
    msg >> entityId;
    RemoveEntity(entityId);
    msg << entityId;
    MessageAllClients(msg, client);
    client->Disconnect();
}

/**
 * @brief Called when a message is received from a client
 *
 * @param client
 * @param msg
 */
void r_type::net::Server::OnMessage(std::shared_ptr<r_type::net::Connection<TypeMessage>> client,
    r_type::net::Message<TypeMessage> &msg)
{
    switch (msg.header.id) {
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
    case TypeMessage::MoveEntityMessage: {
        EntityInformation entity;
        msg >> entity;
        if (CheckPlayerPosition(entity)) {
            UpdateEntity(entity);
            r_type::net::Message<TypeMessage> msg;
            msg.header.id = TypeMessage::UpdateEntity;
            msg << entity;
            MessageAllClients(msg);
        }
    } break;
    case TypeMessage::DestroyEntityMessage: {
        OnClientDisconnect(client, msg);
    } break;
    }
}