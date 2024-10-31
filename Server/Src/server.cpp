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
    if (_nbrOfPlayers == 4) {
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
    RemoveInfoBar(GetClientInfoBarId(client->GetID()));
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
            uint32_t entityId = GetClientPlayerId(client->GetID());
            PlayerMovement playerMovement;
            msg >> playerMovement;
            UpdatePlayerPosition(playerMovement, entityId);
        } break;
        case TypeMessage::DestroyEntityMessage: {
            OnClientDisconnect(client, msg);
        } break;
        case TypeMessage::CreateEntityMessage: { // This is for player missile creation only
            CreatableClientObject incomingObject;
            msg >> incomingObject;
            switch (incomingObject) {
            case CreatableClientObject::PLAYERMISSILE: {
                r_type::net::Message<TypeMessage> ResponseMsg;
                ResponseMsg.header.id = TypeMessage::CreateEntityResponse;
                client->Send(ResponseMsg);
                r_type::net::Message<TypeMessage> MissileMsg;
                MissileMsg.header.id = TypeMessage::CreateEntityMessage;
                MissileMsg << InitiatePlayerMissile(client->GetID());
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
            client->SetStatus(ServerStatus::RUNNING);
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
            response << InitiatePlayer(client->GetID());
            MessageClient(client, response);
            client->_lastMsg = response;
            response.header.id = TypeMessage::CreateInfoBar;
            response << InitInfoBar(client->GetID());
            MessageClient(client, response);
            response.header.id = TypeMessage::CreateEntityMessage;
            MessageAllClients(client->_lastMsg, client);
            client->_lastMsg = response;
        } break;
        case TypeMessage::ReceivePlayerInformation: {
            std::cout << "[" << client->GetID() << "]: Player Information Received" << std::endl;
            r_type::net::Message<TypeMessage> response;
            response.header.id = TypeMessage::CreateEntityMessage;
            response << _background;
            client->_lastMsg = response;
        }
        case TypeMessage::CreateEntityResponse: {
            std::cout << "[" << client->GetID() << "]: Entity Created" << std::endl;
            if (!client->_initEntities.empty()) {
                std::cout << "[" << client->GetID() << "]: Sending Entity Information"
                          << std::endl;
                r_type::net::Message<TypeMessage> response;
                response.header.id = TypeMessage::CreateEntityMessage;
                response << FormatEntityInformation(client->_initEntities.front().getId());
                client->_lastMsg = response;
                client->Send(response);
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