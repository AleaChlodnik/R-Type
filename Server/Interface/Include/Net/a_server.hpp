/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netServer
*/

#pragma once

#include <Components/component_manager.hpp>
#include <Components/components.hpp>
#include <Entities/entity_factory.hpp>
#include <Entities/entity_manager.hpp>
#include <Net/i_server.hpp>
#include <Systems/systems.hpp>
#include <cmath>
#include <entity_struct.hpp>
#include <error_handling.hpp>
#include <filesystem>
#include <fstream>
#include <game_struct.hpp>
#include <iostream>
#include <level.hpp>
#include <macros.hpp>
#include <unordered_map>

namespace r_type {
namespace net {

/**
 * @brief AServer class template for managing server operations.
 *
 * This class template provides a framework for creating and managing a server
 * that handles client connections, messages, and entity updates. It uses the
 * ASIO library for asynchronous network communication and provides various
 * functions for server operations such as starting, stopping, and updating the
 * server, as well as handling client messages and connections.
 *
 * @tparam T The type of data that the server handles.
 */
template <typename T> class AServer : virtual public r_type::net::IServer<T> {
  public:
    /**
     * @brief Constructs an AServer object with the specified port.
     *
     * This constructor initializes the server with the given port number and sets up
     * the necessary components for the server to function. It initializes the ASIO
     * socket with the provided port and creates instances of EntityManager, EntityFactory,
     * and ComponentManager. Additionally, it initiates the background process and creates
     * three basic monster entities using the entity factory.
     *
     * @param port The port number on which the server will listen for incoming connections.
     */
    AServer(uint16_t port)
        : r_type::net::IServer<T>(),
          _asioSocket(_asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port)),
          _port(port)
    {
        srand(time(NULL));
        _componentManager = ComponentManager();
        _entityManager = EntityManager();
        _entityFactory = EntityFactory();
        _level = r_type::Level<T>();
        _level.SetSystem(_componentManager, _entityManager);
    }

    /**
     * @brief Destructor for the AServer class.
     *
     * This destructor ensures that the server is properly stopped
     * by calling the Stop() method when an instance of AServer is destroyed.
     */
    ~AServer() { Stop(); }

    /**
     * @brief Starts the server and begins waiting for client messages.
     *
     * This function attempts to start the server by waiting for client messages
     * and running the ASIO context in a separate thread. If an exception occurs
     * during this process, it will be caught, an error message will be printed
     * to the standard error stream, and the function will return false.
     *
     * @return true if the server started successfully, false otherwise.
     */
    bool Start()
    {
        try {
            WaitForClientMessage();

            _threadContext = std::thread([this]() { _asioContext.run(); });
        } catch (std::exception &e) {
            std::cerr << "[SERVER] Exception: " << e.what() << std::endl;
            return false;
        }
        std::cout << "[SERVER] Started on port " << _port << std::endl;
        return true;
    }

    /**
     * @brief Stops the server.
     *
     * This function stops the server by stopping the ASIO context and joining the thread context.
     * It also prints a message indicating that the server has been stopped.
     */
    void Stop()
    {
        _asioContext.stop();

        if (_threadContext.joinable())
            _threadContext.join();

        if (_asioSocket.is_open())
            _asioSocket.close();

        std::cout << "[SERVER] Stopped!\n";
    }

    /**
     * @brief Waits for a client message asynchronously.
     *
     * This function waits for a client message by asynchronously receiving data from the socket.
     * When a message is received, it checks if the client endpoint protocol is UDPv4.
     * If the protocol is not UDPv4, it recursively calls itself to wait for another client
     * message. If the protocol is UDPv4 and there are no errors, it prints the client endpoint and
     * checks if a connection already exists. If a connection already exists, it returns without
     * further processing. If a connection does not exist, it creates a new client socket, binds it
     * to a local endpoint, and creates a new connection object. It then calls the OnClientConnect
     * function to check if the client connection is approved. If the connection is approved, it
     * adds the new connection to the list of connections, connects it to the client, and prints
     * the connection ID. If the connection is denied, it prints a message indicating the
     * connection was denied. If there is an error during the receive operation, it prints the
     * error message../
     */
    void WaitForClientMessage()
    {
        _asioSocket.async_receive_from(asio::buffer(_tempBuffer.data(), _tempBuffer.size()),
            _clientEndpoint, [this](std::error_code ec, std::size_t bytes_recvd) {
                if (_clientEndpoint.protocol() != asio::ip::udp::v4())
                    return WaitForClientMessage();
                if (!ec) {
                    std::cout << "[SERVER] New Connection: " << _clientEndpoint << std::endl;
                    // check if connection already exists
                    std::cout << "Client endpoint connection: " << _clientEndpoint << std::endl;
                    for (auto &conn : _deqConnections) {
                        std::cout << "Client endpoint: " << conn->getEndpoint() << std::endl;
                        if (conn->getEndpoint() == _clientEndpoint) {
                            std::cout << "[" << conn->GetID() << "] Connection Approved"
                                      << std::endl;
                            std::cout << "[SERVER] Connection already exists" << std::endl;
                            if (OnClientConnect(conn)) {
                                std::cout << "[SERVER] Connection already exists" << std::endl;
                            } else {
                                std::cout << "[-----] Connection Denied" << std::endl;
                            }
                            return;
                        }
                    }

                    asio::ip::udp::socket newSocket(
                        _asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));

                    // create client socket
                    std::shared_ptr<Connection<T>> newConn =
                        std::make_shared<Connection<T>>(Connection<T>::owner::server, _asioContext,
                            std::move(newSocket), _clientEndpoint, _qMessagesIn);

                    if (OnClientConnect(newConn)) {
                        _deqConnections.push_back(std::move(newConn));
                        _deqConnections.back()->ConnectToClient(this, _nIDCounter++);
                        std::cout << "[" << _deqConnections.back()->GetID()
                                  << "] Connection Approved" << std::endl;
                    } else {
                        std::cout << "[-----] Connection Denied" << std::endl;
                    }
                } else {
                    std::cout << "[SERVER] New Connection Error: " << ec.message() << std::endl;
                }
                WaitForClientMessage();
            });
    }

    /**
     * @brief Sends a message to a specific client if the client is connected.
     *        If the client is not connected, it handles the client disconnection.
     *
     * @tparam T The type of the message.
     * @param client A shared pointer to the client connection.
     * @param msg The message to be sent to the client.
     */
    void MessageClient(std::shared_ptr<Connection<T>> client, const Message<T> &msg)
    {
        if (client && client->IsConnected()) {
            client->Send(msg);
        } else {
            OnClientDisconnect(client);

            client.reset();

            _deqConnections.erase(
                std::remove(_deqConnections.begin(), _deqConnections.end(), client),
                _deqConnections.end());
        }
    }

    /**
     * @brief Sends a message to all connected clients, optionally ignoring a specified client.
     *
     * This function iterates through all the connections in the server and sends the provided
     * message to each connected client, except for the client specified by `pIgnoreClient`.
     * If a client is found to be disconnected, it triggers the disconnection handler and removes
     * the client from the list of connections.
     *
     * @tparam T The type of the message.
     * @param msg The message to be sent to all clients.
     * @param pIgnoreClient A shared pointer to a client connection that should be ignored.
     * Defaults to nullptr.
     */
    void MessageAllClients(
        const Message<T> &msg, std::shared_ptr<Connection<T>> pIgnoreClient = nullptr)
    {
        bool bInvalidClientExists = false;

        for (auto &client : _deqConnections) {
            if (client && client->IsConnected()) {
                if (client != pIgnoreClient) {
                    client->Send(msg);
                    if (msg.header.id == TypeMessage::DestroyEntityMessage) {
                        client->_lastMsg = msg;
                        client->SetStatus(ServerStatus::WAITING);
                    }
                    if (msg.header.id == TypeMessage::GameTransitionMode) {
                        client->_lastMsg = msg;
                        client->SetStatus(ServerStatus::TRANSITION);
                    }
                }
            } else {
                OnClientDisconnect(client);
                client.reset();
                bInvalidClientExists = true;
            }
        }

        if (bInvalidClientExists)
            _deqConnections.erase(
                std::remove(_deqConnections.begin(), _deqConnections.end(), nullptr),
                _deqConnections.end());
    }

    /**
     * @brief Updates the information bar for a given player.
     *
     * This function retrieves the health and score components of the specified player,
     * as well as the sprite and text data components of the player's information bar.
     * It then updates the UIEntityInformation structure with these values.
     *
     * @param playerId The ID of the player whose information bar is to be updated.
     * @return UIEntityInformation The updated information for the player's information bar.
     */
    UIEntityInformation UpdateInfoBar(int playerId)
    {
        UIEntityInformation entity;
        int clientId = GetPlayerClientId(playerId);
        int infoBarId = GetClientInfoBarId(clientId);
        auto playerHealth = _componentManager.getComponent<HealthComponent>(playerId);
        auto playerScore = _componentManager.getComponent<ScoreComponent>(playerId);
        auto barSpriteData = _componentManager.getComponent<SpriteDataComponent>(infoBarId);
        auto barTextData = _componentManager.getComponent<TextDataComponent>(infoBarId);
        if (playerHealth && barSpriteData && barTextData) {
            entity.uniqueID = infoBarId;
            entity.spriteData = *(barSpriteData.value());
            entity.textData = *(barTextData.value());
            entity.lives = playerHealth.value()->lives;
            entity.score = playerScore.value()->score;
        }
        return entity;
    }

    /**
     * @brief Updates the server state, processes incoming messages, and updates the game level.
     *
     * This function performs several tasks:
     * - If no players are connected, it returns immediately.
     * - If players are connected and the player connection flag is not set, it sets the flag and
     * updates the clock.
     * - Spawns a thread to update the game level.
     * - Processes up to nMaxMessages from the incoming message queue.
     * - Joins the level update thread and updates the clock if entities were updated.
     *
     * @param nMaxMessages The maximum number of messages to process from the incoming message
     * queue. Default is -1 (process all messages).
     * @param bWait A flag indicating whether to wait for messages. Default is false.
     */
    void Update(size_t nMaxMessages = -1, bool bWait = false)
    {
        if (_nbrOfPlayers == 0) {
            _entityManager.removeAllEntities();
            _componentManager.removeAllComponents();
            _playerConnected = false;
            _bossActive = false;
            _bossDefeated = false;
            _endOfLevel = false;
            return;
        }
        if (_nbrOfPlayers > 0 && !_playerConnected) {
            _playerConnected = true;
            _clock = std::chrono::system_clock::now();
        }
        _level.SetSystem(_componentManager, _entityManager);

        bool bUpdateEntities = false;
        std::chrono::system_clock::time_point newClock = std::chrono::system_clock::now();

        std::thread t_level([this, newClock, &bUpdateEntities]() {
            _level.Update(this, _componentManager, _entityManager, newClock, &bUpdateEntities);
        });

        auto setToAllClients = [this](ServerStatus type) {
            for (auto &client : _deqConnections) {
                if (client && client->IsConnected()) {
                    client->SetStatus(type);
                }
            }
        };

        if (_bossDefeated) {
            if (!_watingPlayersReady) {
                switch (_level.GetLevel()) {
                case GameState::LevelOne: {
                    _level.ChangeLevel(GameState::LevelTwo);
                } break;
                case GameState::LevelTwo: {
                    _level.ChangeLevel(GameState::LevelThree);
                } break;
                case GameState::LevelThree: {
                    _level.ChangeLevel(GameState::Win);
                } break;

                default:
                    break;
                }
                r_type::net::Message<T> msg;
                _watingPlayersReady = true;
                msg.header.id = TypeMessage::GameTransitionMode;
                MessageAllClients(msg);
            }
            if (_playerReady == _nbrOfPlayers) {
                _endOfLevel = false;
                _bossDefeated = false;
                _clock = std::chrono::system_clock::now();
                r_type::net::Message<T> msg;
                msg.header.id = TypeMessage::FinishInitialization;
                MessageAllClients(msg);
                setToAllClients(ServerStatus::RUNNING);
                _watingPlayersReady = false;
                _playerReady = 0;
                _level.ChangeBackground(this, _entityManager, _componentManager);
            }
        }

        size_t nMessageCount = 0;
        while (nMessageCount < nMaxMessages && !_qMessagesIn.empty()) {
            auto msg = _qMessagesIn.pop_front();

            OnMessage(msg.remote, msg.msg);

            nMessageCount++;
        }
        t_level.join();
        if (bUpdateEntities)
            _clock = newClock;
    }

    /**
     * @brief Updates the position of an entity based on the message received and the
     * client ID.
     *
     * This function updates the position of an entity. If the entity is not touching any
     * other player, it updates its position and sends a message to all clients about the
     * new position. If it touches another player, a destroy message is sent to all
     * clients.
     *
     * @param msg The message containing the new position of the entity.
     * @param clientId The ID of the client sending the update.
     */

    void UpdatePlayerPosition(PlayerMovement direction, uint32_t entityId) override
    {
        auto entitySpriteData = _componentManager.getComponent<SpriteDataComponent>(entityId);
        EntityInformation entity;

        auto hitbox = _componentManager.getComponent<HitboxComponent>(entityId);
        auto pos = _componentManager.getComponent<PositionComponent>(entityId);

        vf2d newPos = {pos.value()->x, pos.value()->y};
        switch (direction) {
        case PlayerMovement::UP: {
            newPos.y -= 2;
        } break;
        case PlayerMovement::DOWN: {
            newPos.y += 2;
        } break;
        case PlayerMovement::LEFT: {
            newPos.x -= 2;
        } break;
        case PlayerMovement::RIGHT: {
            newPos.x += 2;
        } break;
        }

        if (hitbox && pos) {
            float halfWidth = hitbox.value()->w / 2;
            float halfHeight = hitbox.value()->h / 2;
            float minX, maxX, minY, maxY;

            maxX = ((newPos.x / 100) * SCREEN_WIDTH) + halfWidth;
            minX = ((newPos.x / 100) * SCREEN_WIDTH) - halfWidth;
            maxY = ((newPos.y / 100) * SCREEN_HEIGHT) + halfHeight;
            minY = ((newPos.y / 100) * SCREEN_HEIGHT) - halfHeight;

            if (maxX > SCREEN_WIDTH || minX < 0 || maxY > (SCREEN_HEIGHT - 30) || minY < 0) {
                return;
            }
            auto vel = _componentManager.getComponent<VelocityComponent>(entityId);
            if (pos && vel) {
                // player go down
                if (pos.value()->y < newPos.y) {
                    vel.value()->y -= 0.1;
                    if (vel.value()->y < -1) {
                        vel.value()->y = -1;
                    }
                } else if (pos.value()->y > newPos.y) {
                    vel.value()->y += 0.1;
                    if (vel.value()->y > 1) {
                        vel.value()->y = 1;
                    }
                }
                pos.value()->x = newPos.x;
                pos.value()->y = newPos.y;

                auto frontComponent = _componentManager.getComponent<FrontComponent>(entityId);
                if (frontComponent.value()->targetId != -1) {
                    std::cout << "frontComponent.targetId: " << frontComponent.value()->targetId
                              << std::endl;
                    auto posFront = _componentManager.getComponent<PositionComponent>(
                        frontComponent.value()->targetId);
                    posFront.value()->x = newPos.x + 2;
                    posFront.value()->y = newPos.y;
                    vf2d newPosFront = {posFront.value()->x, posFront.value()->y};
                    uint32_t entityIdFront = frontComponent.value()->targetId;
                    r_type::net::Message<TypeMessage> moveMsg;
                    moveMsg.header.id = TypeMessage::MoveEntityMessage;
                    moveMsg << entityIdFront << newPosFront;
                    MessageAllClients(moveMsg);
                }
            }

            // std::cout << "Pos: " << newPos.x << " " << newPos.y << std::endl;
            // ////////////////////////////////////////////////

            // Update entity information and send to all clients
            r_type::net::Message<TypeMessage> moveMsg;
            moveMsg.header.id = TypeMessage::MoveEntityMessage;
            moveMsg << entityId << newPos;
            MessageAllClients(moveMsg);
        }
    }

    /**
     * @brief Saves the score of a player to a file.
     *
     * This function saves the score of a player identified by the given playerId
     * to a file named "scores.txt" located in the "GameScores" directory. If the
     * directory or file does not exist, they will be created. The score is appended
     * to the file in the format "Player <playerId>: <score>".
     *
     * @param playerId The unique identifier of the player whose score is to be saved.
     *
     * @throws failedToCreateFile If the file cannot be created.
     * @throws failedToOpenFile If the file cannot be opened in append mode.
     */
    void SavePlayerScore(uint32_t playerId)
    {
        std::string directory = "GameScores";
        std::string filePath = directory + "/scores.txt";
        if (!std::filesystem::exists(directory)) {
            std::filesystem::create_directory(directory);
        }
        if (!std::filesystem::exists(filePath)) {
            std::ofstream outFile(filePath); // Creating the file
            if (!outFile) {
                throw failedToCreateFile();
            }
            outFile.close();
        }
        std::ofstream outFile(filePath, std::ios_base::app); // Open in append mode
        if (!outFile) {
            throw failedToOpenFile();
        }
        if (auto scoreComponent = _componentManager.getComponent<ScoreComponent>(playerId)) {
            std::string playerID = "Player " + std::to_string(playerId);
            outFile << playerID << ": " << scoreComponent.value()->score << "\n";
            outFile.close();
        }
    }

    /**
     * @brief Retrieves the entity ID associated with a client ID.
     *
     * @param id The client ID.
     * @return uint32_t The entity ID associated with the client.
     */
    uint32_t GetClientPlayerId(uint32_t id) { return _clientPlayerID[id]; }

    /**
     * @brief Retrieves the client ID associated with a given player ID.
     *
     * This function searches through the _clientPlayerID map to find the client ID
     * that corresponds to the provided player ID. If the player ID is found, the
     * associated client ID is returned. If the player ID is not found, a
     * playerIdNotFound exception is thrown.
     *
     * @param id The player ID for which the client ID is to be retrieved.
     * @return uint32_t The client ID associated with the given player ID.
     * @throws playerIdNotFound If the player ID is not found in the map.
     */
    uint32_t GetPlayerClientId(uint32_t id)
    {
        for (const auto &pair : _clientPlayerID) {
            if (pair.second == id) {
                return pair.first;
            }
        }
        throw playerIdNotFound();
    }

    /**
     * @brief Retrieves the client info bar ID associated with a given client ID.
     *
     * @param id The client ID for which to retrieve the info bar ID.
     * @return uint32_t The info bar ID associated with the specified client ID.
     */
    uint32_t GetClientInfoBarId(uint32_t id) { return _clientInfoBarID[id]; }

    /**
     * @brief Removes a player from the server.
     *
     * This function removes a player identified by the given ID from the server's
     * internal player list.
     *
     * @param id The unique identifier of the player to be removed.
     */
    void RemovePlayer(uint32_t id) { _clientPlayerID.erase(id); }

    /**
     * @brief Removes an entity from the server.
     *
     * This function removes an entity identified by the given ID from the server.
     * It first checks if the entity exists using the entity manager. If the entity
     * is found, it removes the entity from all components using the component manager
     * and then removes the entity itself from the entity manager.
     *
     * @param id The unique identifier of the entity to be removed.
     */
    void RemoveEntity(uint32_t id)
    {
        if (auto entity = _entityManager.getEntity(id)) {
            _componentManager.removeEntityFromAllComponents(id);
            _entityManager.removeEntity(id);
        }
    }

    /**
     * @brief Removes an information bar and its associated entities.
     *
     * This function removes an information bar identified by the given `infoBarId`.
     * It first checks if the information bar has a `TextDataComponent` and removes
     * all entities associated with the categories listed in the `TextDataComponent`.
     * Finally, it removes the information bar entity itself and erases its ID from
     * the client information bar ID map.
     *
     * @param infoBarId The ID of the information bar to be removed.
     */
    void RemoveInfoBar(uint32_t infoBarId)
    {
        if (auto textDataComponent =
                _componentManager.getComponent<TextDataComponent>(infoBarId)) {
            for (uint32_t categoryId : textDataComponent.value()->categoryIds) {
                if (auto entity = _entityManager.getEntity(categoryId)) {
                    _entityManager.removeEntity(categoryId);
                }
            }
            RemoveEntity(infoBarId);
        }
        _clientInfoBarID.erase(infoBarId);
    }

    void RemoveBossTail(int bossId)
    {
        if (auto bossComp = _componentManager.getComponent<BossComponent>(bossId)) {
            for (size_t i = 0; i < bossComp.value()->tailSegmentIds.size(); i++) {
                int tailSegId = bossComp.value()->tailSegmentIds[i];
                if (auto entity = _entityManager.getEntity(tailSegId)) {
                    r_type::net::Message<TypeMessage> msg;
                    msg.header.id = TypeMessage::DestroyEntityMessage;
                    msg << tailSegId;
                    MessageAllClients(msg);
                    RemoveEntity(tailSegId);
                    // std::cout << "Tail segment removed" << std::endl;
                    // //////////////////////////////////////
                }
            }
        }
        _bossDefeated = true;
    }

    /**
     * @brief Initializes a new player entity and assigns a random position.
     *
     * The function creates a new player entity, assigns it a random position, and ensures
     * that it does not overlap with any other players.
     *
     * @param clientId The client ID of the player being initialized.
     * @return EntityInformation The information of the newly created player entity.
     */
    EntityInformation InitiatePlayer(int clientId)
    {
        EntityInformation entityInfo;
        Entity player =
            _entityFactory.createPlayer(_entityManager, _componentManager, _nbrOfPlayers);
        entityInfo.uniqueID = player.getId();
        auto playerSprite =
            _componentManager.getComponent<SpriteDataComponent>(entityInfo.uniqueID);
        auto playerPos = _componentManager.getComponent<PositionComponent>(entityInfo.uniqueID);
        auto animation = _componentManager.getComponent<AnimationComponent>(entityInfo.uniqueID);
        if (playerSprite && playerPos && animation) {
            entityInfo.ratio.x =
                (animation.value()->dimension.x * playerSprite.value()->scale.x) / SCREEN_WIDTH;
            entityInfo.ratio.y =
                (animation.value()->dimension.y * playerSprite.value()->scale.y) / SCREEN_HEIGHT;
            entityInfo.spriteData = *(playerSprite.value());
            entityInfo.vPos.x = playerPos.value()->x;
            entityInfo.vPos.y = playerPos.value()->y;
            entityInfo.animationComponent.dimension = animation.value()->dimension;
            entityInfo.animationComponent.offset = animation.value()->offset;
        }
        _clientPlayerID.insert_or_assign(clientId, entityInfo.uniqueID);
        return entityInfo;
    }

    UIEntityInformation InitInfoBar(int clientId)
    {
        UIEntityInformation entityInfo;
        Entity infoBar = _entityFactory.createInfoBar(_entityManager, _componentManager);
        entityInfo.uniqueID = infoBar.getId();
        std::cout << "GameBarInformation" << std::endl;
        std::cout << "Entity ID: " << entityInfo.uniqueID << std::endl;
        std::cout << "Info: " << entityInfo.lives << ", " << entityInfo.score << std::endl;
        std::cout << "SpriteData: " << entityInfo.spriteData.spritePath << ", "
                  << entityInfo.spriteData.scale.x << ", " << entityInfo.spriteData.scale.y << ", "
                  << std::endl;
        auto spriteData = _componentManager.getComponent<SpriteDataComponent>(entityInfo.uniqueID);
        auto textData = _componentManager.getComponent<TextDataComponent>(entityInfo.uniqueID);
        auto health = _componentManager.getComponent<HealthComponent>(GetClientPlayerId(clientId));
        if (spriteData && textData && health) {
            entityInfo.spriteData = *(spriteData.value());
            entityInfo.textData = *(textData.value());
            entityInfo.textData.categorySize = textData.value()->categorySize;
            entityInfo.lives = health.value()->lives;
        }
        _clientInfoBarID.insert_or_assign(clientId, entityInfo.uniqueID);
        return entityInfo;
    }

    /**
     * @brief Formats the information of a given entity into an EntityInformation structure.
     *
     * This function retrieves the position and sprite data components of the specified entity
     * and populates an EntityInformation structure with this data. If the entity has both
     * position and sprite data components, their values are copied into the EntityInformation
     * structure. If either component is missing, the EntityInformation structure will be
     * returned with default values.
     *
     * @param entity The entity whose information is to be formatted.
     * @return EntityInformation The formatted information of the entity.
     */
    EntityInformation FormatEntityInformation(uint32_t entityId)
    {
        EntityInformation entityInfo;
        auto entityPos = _componentManager.getComponent<PositionComponent>(entityId);
        auto sprite = _componentManager.getComponent<SpriteDataComponent>(entityId);
        auto animation = _componentManager.getComponent<AnimationComponent>(entityId);
        if (entityPos && sprite) {
            entityInfo.uniqueID = entityId;
            entityInfo.vPos.x = entityPos.value()->x;
            entityInfo.vPos.y = entityPos.value()->y;
            entityInfo.spriteData = *(sprite.value());
            if (animation) {
                entityInfo.ratio.x =
                    (animation.value()->dimension.x * sprite.value()->scale.x) / SCREEN_WIDTH;
                entityInfo.ratio.y =
                    (animation.value()->dimension.y * sprite.value()->scale.y) / SCREEN_HEIGHT;
                entityInfo.animationComponent.dimension = animation.value()->dimension;
                entityInfo.animationComponent.offset = animation.value()->offset;
            }
        }
        return entityInfo;
    }

    /**
     * @brief Initializes a missile entity associated with a player.
     *
     * The function creates a missile entity associated with a player and assigns its
     * position based on the player's current position.
     *
     * @param clientId The client ID of the player firing the missile.
     * @return EntityInformation The information of the newly created missile entity.
     */
    EntityInformation InitiatePlayerMissile(int entityId)
    {
        EntityInformation entityInfo;
        entityInfo.uniqueID = entityId;
        auto missilePos = _componentManager.getComponent<PositionComponent>(entityInfo.uniqueID);
        auto sprite = _componentManager.getComponent<SpriteDataComponent>(entityInfo.uniqueID);
        auto animation = _componentManager.getComponent<AnimationComponent>(entityInfo.uniqueID);
        if (missilePos && sprite) {
            entityInfo.vPos.x = missilePos.value()->x;
            entityInfo.vPos.y = missilePos.value()->y;
            entityInfo.spriteData = *(sprite.value());
            if (animation) {
                entityInfo.ratio.x =
                    (animation.value()->dimension.x * sprite.value()->scale.x) / SCREEN_WIDTH;
                entityInfo.ratio.y =
                    (animation.value()->dimension.y * sprite.value()->scale.y) / SCREEN_HEIGHT;
                entityInfo.animationComponent.dimension = animation.value()->dimension;
                entityInfo.animationComponent.offset = animation.value()->offset;
            }
        }
        return entityInfo;
    }

    EntityInformation InitiateEnemyMissile(int enemyId)
    {
        EntityInformation entityInfo;
        Entity missile =
            _entityFactory.createEnemyMissile(_entityManager, _componentManager, enemyId);
        entityInfo.uniqueID = missile.getId();
        auto missilePos = _componentManager.getComponent<PositionComponent>(entityInfo.uniqueID);
        auto sprite = _componentManager.getComponent<SpriteDataComponent>(entityInfo.uniqueID);
        auto animation = _componentManager.getComponent<AnimationComponent>(entityInfo.uniqueID);
        if (missilePos && sprite) {
            entityInfo.vPos.x = missilePos.value()->x;
            entityInfo.vPos.y = missilePos.value()->y;
            if (animation) {
                entityInfo.ratio.x =
                    (animation.value()->dimension.x * sprite.value()->scale.x) / SCREEN_WIDTH;
                entityInfo.ratio.y =
                    (animation.value()->dimension.y * sprite.value()->scale.y) / SCREEN_HEIGHT;
                entityInfo.animationComponent.dimension = animation.value()->dimension;
                entityInfo.animationComponent.offset = animation.value()->offset;
            }
            entityInfo.spriteData = *(sprite.value());
        }
        return entityInfo;
    }

    EntityInformation InitiateWeaponForce(int entityId)
    {
        EntityInformation entityInfo;
        entityInfo.uniqueID = entityId;
        auto position = _componentManager.getComponent<PositionComponent>(entityInfo.uniqueID);
        auto sprite = _componentManager.getComponent<SpriteDataComponent>(entityInfo.uniqueID);
        auto animation = _componentManager.getComponent<AnimationComponent>(entityInfo.uniqueID);
        if (position && sprite) {
            entityInfo.vPos.x = position.value()->x;
            entityInfo.vPos.y = position.value()->y;
            entityInfo.spriteData = *(sprite.value());
            if (animation) {
                entityInfo.ratio.x =
                    (animation.value()->dimension.x * sprite.value()->scale.x) / SCREEN_WIDTH;
                entityInfo.ratio.y =
                    (animation.value()->dimension.y * sprite.value()->scale.y) / SCREEN_HEIGHT;
                entityInfo.animationComponent.dimension = animation.value()->dimension;
                entityInfo.animationComponent.offset = animation.value()->offset;
            }
        }
        return entityInfo;
    }

    void InitBoss(r_type::net::AServer<T> *server)
    {
        server->_bossActive = true;
        // r_type::net::Message<TypeMessage> msg;
        // msg.header.id = TypeMessage::ChangeBackgroundMusic;
        // msg << 1;
        // server->MessageAllClients(msg);
        Entity boss = _entityFactory.createBoss(_entityManager, _componentManager, _entityFactory);
        int bossId = boss.getId();
        float segmentOffsetX = -2.0f;
        float segmentOffsetY = -2.0f;
        auto bossComp = _componentManager.getComponent<BossComponent>(bossId);
        auto bossPos = _componentManager.getComponent<PositionComponent>(bossId);
        auto bossSpriteData = _componentManager.getComponent<SpriteDataComponent>(bossId);
        auto bossAnimation = _componentManager.getComponent<AnimationComponent>(bossId);

        if (bossComp && bossPos && bossSpriteData && bossAnimation) {
            int firstTailSegId = bossComp.value()->tailSegmentIds[0];
            if (auto firstTailSegPos =
                    _componentManager.getComponent<PositionComponent>(firstTailSegId)) {
                firstTailSegPos.value()->x = 76;
                firstTailSegPos.value()->y = 88;
            }

            for (size_t i = 1; i < bossComp.value()->tailSegmentIds.size(); i++) {
                int tailSegId = bossComp.value()->tailSegmentIds[i];
                if (auto tailSegPos =
                        _componentManager.getComponent<PositionComponent>(tailSegId)) {
                    int precedingTailSegId = bossComp.value()->tailSegmentIds[i - 1];
                    if (auto precedingTailSegPos =
                            _componentManager.getComponent<PositionComponent>(
                                precedingTailSegId)) {
                        tailSegPos.value()->x = precedingTailSegPos.value()->x + segmentOffsetX;
                        tailSegPos.value()->y = precedingTailSegPos.value()->y + segmentOffsetY;
                    }
                }
            }

            EntityInformation bossEntityInfo;
            bossEntityInfo.uniqueID = bossId;

            bossEntityInfo.vPos.x = bossPos.value()->x;
            bossEntityInfo.vPos.y = bossPos.value()->y;
            bossEntityInfo.spriteData = *(bossSpriteData.value());
            bossEntityInfo.ratio.x =
                (bossAnimation.value()->dimension.x * bossSpriteData.value()->scale.x) /
                SCREEN_WIDTH;
            bossEntityInfo.ratio.y =
                (bossAnimation.value()->dimension.y * bossSpriteData.value()->scale.y) /
                SCREEN_HEIGHT;

            bossEntityInfo.animationComponent.dimension = bossAnimation.value()->dimension;
            bossEntityInfo.animationComponent.offset = bossAnimation.value()->offset;

            r_type::net::Message<TypeMessage> bossMsg;
            bossMsg.header.id = TypeMessage::CreateEntityMessage;
            bossMsg << bossEntityInfo;
            server->MessageAllClients(bossMsg);

            for (int i = 0; i != bossComp.value()->tailSegmentIds.size(); i++) {
                EntityInformation tailSegEntityInfo;
                tailSegEntityInfo.uniqueID = bossComp.value()->tailSegmentIds[i];
                auto tailSpriteData = _componentManager.getComponent<SpriteDataComponent>(
                    tailSegEntityInfo.uniqueID);
                auto tailPos =
                    _componentManager.getComponent<PositionComponent>(tailSegEntityInfo.uniqueID);
                auto tailAnimation =
                    _componentManager.getComponent<AnimationComponent>(tailSegEntityInfo.uniqueID);
                if (tailSpriteData && tailPos && tailAnimation) {
                    tailSegEntityInfo.vPos.x = tailPos.value()->x;
                    tailSegEntityInfo.vPos.y = tailPos.value()->y;
                    tailSegEntityInfo.spriteData = *(tailSpriteData.value());
                    tailSegEntityInfo.ratio.x =
                        (tailAnimation.value()->dimension.x * tailSpriteData.value()->scale.x) /
                        SCREEN_WIDTH;
                    tailSegEntityInfo.ratio.y =
                        (tailAnimation.value()->dimension.y * tailSpriteData.value()->scale.y) /
                        SCREEN_HEIGHT;
                    tailSegEntityInfo.animationComponent.dimension =
                        tailAnimation.value()->dimension;
                    tailSegEntityInfo.animationComponent.offset = tailAnimation.value()->offset;
                }
                r_type::net::Message<TypeMessage> tailMsg;
                tailMsg.header.id = TypeMessage::CreateEntityMessage;
                tailMsg << tailSegEntityInfo;
                server->MessageAllClients(tailMsg);
            }
        }
    }

    std::shared_ptr<Connection<T>> getClientById(
        const std::deque<std::shared_ptr<Connection<T>>> &connections, uint32_t clientId)
    {
        for (const auto &client : connections) {
            if (client && client->GetID() == clientId) {
                return client;
            }
        }
        return nullptr;
    }

    /**
     * @brief Callback function that is called when a client has been successfully
     * validated.
     *
     * This function is intended to be overridden by derived classes to handle any
     * specific actions that need to be taken when a client is validated.
     *
     * @param client A shared pointer to the validated client connection.
     */
    virtual void OnClientValidated(std::shared_ptr<Connection<T>> client) {}

    /**
     * @brief Retrieves the component manager associated with the server.
     *
     * This function provides access to the component manager, which is responsible for managing
     * the components associated with entities in the game. It allows for the retrieval and
     * manipulation of entity components, enabling the game logic to interact with them as needed.
     *
     * @return ComponentManager& A reference to the component manager instance.
     */
    ComponentManager GetComponentManager() override { return _componentManager; }

    /**
     * @brief Retrieves the entity manager associated with the server.
     *
     * This function returns the entity manager responsible for creating, managing, and removing
     * entities in the game. The entity manager handles the lifecycle of entities and ensures that
     * they are correctly processed within the game's systems.
     *
     * @return EntityManager& A reference to the entity manager instance.
     */
    EntityManager &GetEntityManager() override { return _entityManager; }

    /**
     * @brief Retrieves the entity factory associated with the server.
     *
     * This function provides access to the entity factory, which is responsible for creating
     * new entities in the game. The entity factory provides methods to instantiate various types
     * of entities, such as players, missiles, and background elements, ensuring that they are
     * correctly initialized with the necessary components.
     *
     * @return EntityFactory& A reference to the entity factory instance.
     */
    EntityFactory &GetEntityFactory() override { return _entityFactory; }

    /**
     * @brief Retrieves the current clock time of the server.
     *
     * This function returns the current time point of the server's clock, which can be used
     * for time-related calculations, such as updating game state, handling animations,
     * or scheduling events. It provides a consistent reference point for the server's operations.
     *
     * @return std::chrono::system_clock::time_point The current time point of the server's clock.
     */
    std::chrono::system_clock::time_point GetClock() override { return _clock; }

    /**
     * @brief Set the Clock object
     *
     * @param clock
     */
    void SetClock(std::chrono::system_clock::time_point clock) { _clock = clock; }

  protected:
    /**
     * @brief on client connect event
     *
     * @param client
     * @return true
     * @return false
     */
    virtual bool OnClientConnect(std::shared_ptr<Connection<T>> client) { return false; }

    /**
     * @brief on client disconnect event
     *
     * @param client
     */
    virtual void OnClientDisconnect(std::shared_ptr<Connection<T>> client) {}

    /**
     * @brief on message event
     *
     * @param client
     * @param msg
     */
    virtual void OnMessage(std::shared_ptr<Connection<T>> client, Message<T> &msg) {}

  public:
    /**
     * @brief Thread-safe queue to store incoming messages.
     *
     * This member variable is a thread-safe queue that holds messages
     * of type OwnedMessage<T>. It ensures that messages can be safely
     * accessed and modified by multiple threads concurrently.
     */
    ThreadSafeQueue<OwnedMessage<T>> _qMessagesIn;

    /**
     * @brief A deque that holds shared pointers to Connection objects.
     *
     * This member variable is used to manage a collection of active connections.
     * The use of std::shared_ptr ensures that the Connection objects are
     * reference-counted and automatically deallocated when no longer in use.
     *
     * @tparam T The type of data that the Connection handles.
     */
    std::deque<std::shared_ptr<Connection<T>>> _deqConnections;

    /**
     * @brief The io_context object provides I/O services, such as sockets, that the server
     * will use.
     *
     * This member variable is responsible for managing asynchronous I/O operations.
     * It is part of the ASIO library, which is used for network programming.
     */
    asio::io_context _asioContext;
    /**
     * @brief Thread object for managing the server's context operations.
     *
     * This member variable represents a thread that handles the server's context,
     * allowing for concurrent execution of tasks related to the server's operation.
     * It is used to ensure that the server can perform its duties without blocking
     * the main execution flow.
     */
    std::thread _threadContext;

    /**
     * @brief A socket for sending and receiving UDP datagrams.
     *
     * This member variable represents a UDP socket using the ASIO library.
     * It is used for network communication in the server.
     */
    asio::ip::udp::socket _asioSocket;
    /**
     * @brief Represents the endpoint of a client in a UDP connection.
     *
     * This member variable holds the endpoint information (IP address and port)
     * of a client in a UDP connection using the ASIO library.
     */
    asio::ip::udp::endpoint _clientEndpoint;

    /**
     * @brief Temporary buffer used for storing data.
     *
     * This buffer is an array of 1024 bytes (uint8_t) used for temporary storage
     * of data within the server's network interface.
     */
    std::array<uint8_t, 1024> _tempBuffer;

    /**
     * @brief Counter for generating unique network IDs.
     *
     * This variable is used to keep track of the current ID to be assigned
     * for network-related entities. It starts at 10000 and increments with
     * each new ID generation.
     */
    uint32_t _nIDCounter = 10000;

    /**
     * @brief Manages and maintains the lifecycle of various components within the server.
     *
     * The ComponentManager is responsible for creating, updating, and destroying
     * components as needed. It ensures that all components are properly managed and that
     * their states are consistent throughout the server's operation.
     */
    ComponentManager _componentManager;
    /**
     * @brief Manages the lifecycle and operations of entities within the server.
     *
     * The EntityManager is responsible for creating, updating, and deleting entities.
     * It ensures that entities are properly managed and synchronized within the server's
     * environment.
     */
    EntityManager _entityManager;
    /**
     * @brief An instance of EntityFactory used to create and manage game entities.
     */
    EntityFactory _entityFactory;

    bool _endOfLevel = false;
    bool _bossActive = false;
    bool _bossDefeated = false;
    bool _watingPlayersReady = false;

    /**
     * @brief A container that maps client IDs to player IDs.
     *
     * left: client ID
     * right: player ID
     *
     * This unordered map is used to associate client IDs with their corresponding player
     * IDs. The keys are of type uint32_t representing the client IDs, and the values are
     * also of type uint32_t representing the player IDs.
     */
    std::unordered_map<uint32_t, uint32_t> _clientPlayerID;

    std::unordered_map<uint32_t, uint32_t> _clientInfoBarID;

    /**
     * @brief Number of players currently connected to the server.
     */
    int _nbrOfPlayers = 0;

    /**
     * @brief Stores the current time point from the system clock.
     *
     * This variable is initialized with the current time using
     * std::chrono::system_clock::now() and represents a specific
     * point in time according to the system clock.
     */
    std::chrono::system_clock::time_point _clock = std::chrono::system_clock::now();
    bool _playerConnected = false;

    /**
     * @brief Holds information about the background entity.
     *
     * This member variable stores the details related to the background entity
     * in the game. It includes properties such as position, texture, and other
     * relevant attributes that define the background's appearance and behavior.
     */
    EntityInformation _background;

    int _port;

    r_type::Level<T> _level;

    int _playerReady = 0;
};
} // namespace net
} // namespace r_type