/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <Net/server.hpp>
#include <creatable_client_object.hpp>

/**
 * @brief Handles the event when a client attempts to connect to the server.
 *
 * This function checks if the maximum number of players (4) has been reached.
 * If so, it sends a denial message to the client and returns false.
 * Otherwise, it sends an acceptance message to the client, increments the
 * number of players, sets the client's status to INITIALISATION, assigns the
 * last message sent to the client, and initializes the client's entities.
 *
 * @param client A shared pointer to the client connection attempting to connect.
 * @return true if the client is accepted, false if the client is denied.
 */
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
    msg << _nbrOfPlayers;
    MessageClient(client, msg);
    _nbrOfPlayers++;
    client->SetStatus(ServerStatus::INITIALISATION);
    client->_lastMsg = msg;
    client->_initEntities = _entityManager.getAllEntities();
    if (_nbrOfPlayers == 0)
        _watingPlayersReady = true;
    return true;
}

/**
 * @brief Handles the disconnection of a client from the server.
 *
 * This function is called when a client disconnects from the server. It performs
 * several tasks including removing the client, saving the player's score, removing
 * associated entities, and notifying all other clients about the disconnection.
 *
 * @param client A shared pointer to the connection object representing the client.
 * @param msg A reference to the message object containing information about the disconnection.
 */
void r_type::net::Server::OnClientDisconnect(
    std::shared_ptr<r_type::net::Connection<TypeMessage>> client,
    r_type::net::Message<TypeMessage> &msg)
{
    uint32_t entityId;
    std::cout << "[" << client->GetID() << "]: Removing client" << std::endl;
    msg >> entityId;
    SavePlayerScore(entityId);
    RemoveEntity(entityId);
    auto linkForce = _componentManager.getComponent<LinkForceComponent>(entityId);
    if (linkForce) {
        RemoveEntity(linkForce.value()->targetId);
    }
    RemovePlayer(client->GetID());
    msg << entityId;
    MessageAllClients(msg, client);
    _nbrOfPlayers--;
    RemoveInfoBar(GetClientInfoBarId(client->GetID()));
    client->Disconnect();
}

/**
 * @brief Handles the reception of a message from a client.
 *
 * This function is called when a message is received from a client. It processes
 * the message based on the client's status and the message's ID. The function
 * performs different actions based on the message ID, such as sending a response
 * message, updating player positions, creating entities, or destroying entities.
 *
 * @param client A shared pointer to the connection object representing the client.
 * @param msg A reference to the message object containing information sent by the client.
 */
void r_type::net::Server::OnMessage(std::shared_ptr<r_type::net::Connection<TypeMessage>> client,
    r_type::net::Message<TypeMessage> &msg)
{
    switch (client->GetStatus()) {
    case ServerStatus::RUNNING: {
        switch (msg.header.id) {
        case TypeMessage::ServerPing: {
            std::cout << "[" << client->GetID() << "]: Server Ping" << std::endl;
            client->Send(msg);
        } break;

        case TypeMessage::MessageAll: {
            std::cout << "[" << client->GetID() << "]: Message All" << std::endl;
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

                uint32_t playerId = GetClientPlayerId(client->GetID());
                auto frontComponent = _componentManager.getComponent<FrontComponent>(playerId);
                if (frontComponent) {
                    if (frontComponent.value()->targetId == -1) {
                        Entity missile = _entityFactory.createPlayerMissile(
                            _entityManager, _componentManager, playerId);
                        r_type::net::Message<TypeMessage> MissileMsg;
                        MissileMsg.header.id = TypeMessage::CreateEntityMessage;
                        MissileMsg << InitiatePlayerMissile(missile.getId());
                        MessageAllClients(MissileMsg);
                    } else {
                        Entity ForceMissile = _entityFactory.createForceMissile(
                            _entityManager, _componentManager, frontComponent.value()->targetId);
                        r_type::net::Message<TypeMessage> MissileMsg;
                        MissileMsg.header.id = TypeMessage::CreateEntityMessage;
                        MissileMsg << InitiatePlayerMissile(ForceMissile.getId());
                        MessageAllClients(MissileMsg);
                    }
                }
            } break;
            default: {
            } break;
            }
        } break;
        }
    } break;
    case ServerStatus::WAITING: {
        switch (msg.header.id) {
        case TypeMessage::DestroyEntityResponse: {
            std::cout << "[" << client->GetID() << "]: Entity Destroyed" << std::endl;
            if (client->GetLastStatus() == ServerStatus::INITIALISATION)
                client->SetStatus(ServerStatus::INITIALISATION);
            else if (client->GetLastStatus() == ServerStatus::TRANSITION)
                client->SetStatus(ServerStatus::TRANSITION);
            else {
                client->SetStatus(ServerStatus::RUNNING);
                std::cout << "[" << client->GetID() << "]: Sending Last Message" << std::endl;
            }
        }
        default: {
            if (client->_lastMsg.size() > 0)
                client->Send(client->_lastMsg);
        } break;
        }
    } break;
    case ServerStatus::INITIALISATION: {
        switch (msg.header.id) {
        case TypeMessage::GameEntityInformation: {
            std::cout << "[" << client->GetID() << "]: Game Entity Information Received"
                      << std::endl;
            r_type::net::Message<TypeMessage> response;
            response.header.id = TypeMessage::PlayerInformation;
            response << InitiatePlayer(client->GetID());
            MessageClient(client, response);
            client->_lastMsg = response;
            response.header.id = TypeMessage::CreateEntityMessage;
            MessageAllClients(response, client);
        } break;
        case TypeMessage::GameParametersInformation: {
            std::cout << "[" << client->GetID() << "]: Game Parameters Information Received"
                      << std::endl;
            GameParameters gameParameters;
            msg >> gameParameters;
            std::cout << "Game Parameters: " << gameParameters.nbrOfBasicMonster << std::endl;
            _level.SetGameParameters(gameParameters);
            r_type::net::Message<TypeMessage> response;
            response.header.id = TypeMessage::PlayerInformation;
            response << InitiatePlayer(client->GetID());
            MessageClient(client, response);
            std::cout << "[" << client->GetID() << "]: Sending Player Information" << std::endl;
            response.header.id = TypeMessage::CreateEntityMessage;
            MessageAllClients(response, client);
            response.header.id = TypeMessage::PlayerInformation;
            client->_lastMsg = response;
        } break;
        case TypeMessage::GameBarInformationResponse: {
            std::cout << "[" << client->GetID() << "]: Game Bar Information Received" << std::endl;
            r_type::net::Message<TypeMessage> response;
            response.header.id = TypeMessage::CreateEntityMessage;
            response << _level.GetEntityBackGround(this, _entityManager, _componentManager);
            MessageClient(client, response);
            client->_lastMsg = response;
        } break;
        case TypeMessage::PlayerInformationResponse: {
            std::cout << "[" << client->GetID() << "]: Player Information Received" << std::endl;
            r_type::net::Message<TypeMessage> response;
            response.header.id = TypeMessage::GameBarInformation;
            UIEntityInformation entity = InitInfoBar(client->GetID());
            response << entity;
            MessageClient(client, response);
            client->_lastMsg = response;
        } break;
        case TypeMessage::CreateEntityResponse: {
            if (client->_lastMsg.size() > 0 &&
                client->_lastMsg.header.id != TypeMessage::CreateEntityMessage)
                return;
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
            if (client->_lastMsg.size() > 0 &&
                client->_lastMsg.header.id != TypeMessage::ServerAccept) {
                client->Send(client->_lastMsg);
                std::cout << "[" << client->GetID() << "]: Sending Last Message" << std::endl;
            }
        } break;
        }
    } break;
    case ServerStatus::TRANSITION: {
        switch (msg.header.id) {
        case TypeMessage::GameTransitionResponse: {
            std::cout << "[" << client->GetID() << "]: Game Transition Response Received"
                      << std::endl;
            r_type::net::Message<TypeMessage> response;
            response.header.id = TypeMessage::IsPlayerReady;
            MessageClient(client, response);
            client->_lastMsg = response;
        } break;
        case TypeMessage::PlayerReady: {
            std::cout << "[" << client->GetID() << "]: Player Ready Response Received"
                      << std::endl;
            _level.ChangeBackground(this, _entityManager, _componentManager);
            _playerReady++;
        }
        }
        break;
    default: {
        if (client->_lastMsg.size() > 0)
            client->Send(client->_lastMsg);
    } break;
    } break;
    }
}