/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <Net/server.hpp>
#include <creatable_client_object.hpp>

bool r_type::net::Server::OnClientConnect(
    std::shared_ptr<r_type::net::Connection<TypeMessage>> client)
{
    r_type::net::Message<TypeMessage> msg;
    msg.header.id = TypeMessage::ServerAccept;
    msg << InitiatePlayers(client->GetID());
    nbrOfPlayers++;
    MessageClient(client, msg);

    msg.header.id = TypeMessage::CreateEntityMessage;
    MessageAllClients(msg, client);
    msg << background;
    MessageClient(client, msg);
    EntityInformation entity;
    InitListEntities(client, GetClientEntityId(client.get()->GetID()));
    const std::vector<Entity> entities = entityManager.getAllEntities();
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
    uint32_t entityId;
    std::cout << "[" << client->GetID() << "]: Removing client" << std::endl;
    msg >> entityId;
    RemovePlayer(client->GetID());
    RemoveEntities(entityId);
    msg << entityId;
    MessageAllClients(msg, client);
    nbrOfPlayers--;
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
        UpdateEntityPosition(msg, client->GetID());
    } break;
    case TypeMessage::DestroyEntityMessage: {
        OnClientDisconnect(client, msg);
    } break;
    case TypeMessage::CreateEntityMessage: {
        CreatableClientObject tkt;
        msg >> tkt;
        switch (tkt) {
        case CreatableClientObject::MISSILE: {
            r_type::net::Message<TypeMessage> ResponseMsg;
            ResponseMsg.header.id = TypeMessage::CreateEntityResponse;
            client->Send(ResponseMsg);
            r_type::net::Message<TypeMessage> MissileMsg;
            MissileMsg.header.id = TypeMessage::CreateEntityMessage;
            MissileMsg << InitiateMissile(client->GetID());
            MessageAllClients(MissileMsg);
        } break;
        default: {
        } break;
        }
    } break;
    }
}
