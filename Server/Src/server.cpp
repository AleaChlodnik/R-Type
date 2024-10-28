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
    if (_nbrOfPlayers == 3) {
        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::ServerDeny;
        MessageClient(client, msg);
        return false;
    }
    r_type::net::Message<TypeMessage> msg;
    msg.header.id = TypeMessage::ServerAccept;
    MessageClient(client, msg);
    _nbrOfPlayers++;
    client->SetStatus(ServerStatus::INITIALISATION);
    client->_lastMsg = msg;
    client->_initEntities = _entityManager.getAllEntities();
    InitListEntities(client, GetClientPlayerId(client.get()->GetID()));
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
    RemoveEntity(entityId);
    RemovePlayer(client->GetID());
    msg << entityId;
    MessageAllClients(msg, client);
    _nbrOfPlayers--;
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
    std::cout << "[" << client->GetID() << "]: Message Received"
              << " server status: " << client->GetStatus() << std::endl;
    switch (client->GetStatus()) {
    case ServerStatus::RUNNING: {
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
        case TypeMessage::MoveEntityMessage: { // This is only for the players
            std::cout << "[" << client->GetID() << "]: Move Entity" << std::endl;
            UpdatePlayerPosition(msg, client->GetID());
        } break;
        case TypeMessage::DestroyEntityMessage: {
            OnClientDisconnect(client, msg);
        } break;
        case TypeMessage::CreateEntityMessage: { // This is for player missile creation only
            CreatableClientObject incomingObject;
            msg >> incomingObject;
            switch (incomingObject) {
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
    } break;
    case ServerStatus::WAITING: {
        switch (msg.header.id) {
        case TypeMessage::CreateEntityResponse: {
            std::cout << "[" << client->GetID() << "]: Entity Created" << std::endl;
        } break;
        case TypeMessage::DestroyEntityResponse: {
            std::cout << "[" << client->GetID() << "]: Entity Destroyed" << std::endl;
        }
        default: {
            client->Send(client->_lastMsg);
        } break;
        }
    }
    case ServerStatus::INITIALISATION: {
        switch (msg.header.id) {
        case TypeMessage::SendPlayer: {
            std::cout << "[" << client->GetID() << "]: Player Information Sent" << std::endl;
            r_type::net::Message<TypeMessage> response;
            response.header.id = TypeMessage::SendPlayerInformation;
            response << InitiatePlayers(client->GetID());
            MessageClient(client, response);
            client->_lastMsg = response;
        } break;
        case TypeMessage::RecievePlayerInformation: {
            std::cout << "[" << client->GetID() << "]: Player Information Received" << std::endl;
            r_type::net::Message<TypeMessage> response;
            response.header.id = TypeMessage::CreateEntityMessage;
            response << _background;
            client->_lastMsg = response;
        }
        case TypeMessage::CreateEntityResponse: {
            std::cout << "[" << client->GetID() << "]: Entity Created" << std::endl;
            if (!client->_initEntities.empty()) {
                std::cout << "[" << client->GetID() << "]: Sending Entity Information" << std::endl;
                r_type::net::Message<TypeMessage> response;
                response.header.id = TypeMessage::CreateEntityMessage;
                response << FormatEntityInformation(client->_initEntities.front());
                client->_lastMsg = response;
                client->_initEntities.erase(client->_initEntities.begin());
            } else {
                std::cout << "[" << client->GetID() << "]: Finished Initialization" << std::endl;
                client->SetStatus(ServerStatus::RUNNING);
            }
        } break;
        default: {
            client->Send(client->_lastMsg);
        } break;
        }
    }
    }
}
/**
 * @brief Sends a list of existing entities to a newly connected client for initialization.
 *
 * The function iterates through all existing entities and sends their information to the
 * newly connected client, excluding specific entities such as the client itself.
 *
 * @param client The connection to the client.
 * @param entityID The ID of the entity to exclude (usually the client's own entity).
 */
void r_type::net::Server::InitListEntities(
    std::shared_ptr<r_type::net::Connection<TypeMessage>> client, u_int32_t entityID)
{
    EntityInformation entityInfo;
    r_type::net::Message<TypeMessage> msgAddPlayer;
    msgAddPlayer.header.id = TypeMessage::CreateEntityMessage;
    const std::vector<Entity> entities = _entityManager.getAllEntities();
    for (const auto &entity : entities) {
        if (entity.getId() != entityID && entity.getId() != 1) {
            auto playerPos = _componentManager.getComponent<PositionComponent>(entity.getId());
            auto sprite = _componentManager.getComponent<SpriteDataComponent>(entity.getId());
            auto animation = _componentManager.getComponent<AnimationComponent>(entity.getId());
            if (playerPos && sprite) {
                entityInfo.uniqueID = entity.getId();
                entityInfo.vPos.x = playerPos.value()->x;
                entityInfo.vPos.y = playerPos.value()->y;
                if (animation) {
                    entityInfo.animationComponent.dimension = animation.value()->dimension;
                    entityInfo.animationComponent.offset = animation.value()->offset;
                }
                entityInfo.spriteData = *(sprite.value());
                msgAddPlayer << entityInfo;
                MessageClient(client, msgAddPlayer);
            }
        }
    }
    msgAddPlayer.header.id = TypeMessage::FinishInitialization;
    MessageClient(client, msgAddPlayer);
}