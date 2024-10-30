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
          _asioSocket(_asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
    {
        _componentManager = ComponentManager();
        _entityManager = EntityManager();
        _entityFactory = EntityFactory();

        _moveSystem = std::make_shared<MoveSystem>(_componentManager, _entityManager);
        _collisionSystem = std::make_shared<CollisionSystem>(_componentManager, _entityManager);
        _animationSystem = std::make_shared<AnimationSystem>(_componentManager, _entityManager);
        _autoFireSystem = std::make_shared<AutoFireSystem>(_componentManager, _entityManager);

        _background = InitiateBackground();
        _entityFactory.createShooterEnemy(_entityManager, _componentManager);
        _entityFactory.createBasicMonster(_entityManager, _componentManager);
    }

    /**
     * @brief Destructor for the AServer class.
     *
     * This destructor ensures that the server is properly stopped
     * by calling the Stop() method when an instance of AServer is destroyed.
     */
    ~AServer() { Stop(); }

    /**
     * @brief Start the server
     *
     * @return true
     * @return false
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
        std::cout << "[SERVER] Started!" << std::endl;
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
     * @brief Updates the game level based on the provided clock time.
     *
     * This function performs several tasks to update the game level:
     * 1. Checks if the time difference between the new clock and the stored clock exceeds 100
     * milliseconds.
     * 2. If so, it updates entity positions, handles collisions, updates animations, and processes
     * auto-firing.
     * 3. Sends appropriate messages to clients about entity updates, creations, and destructions.
     *
     * @param newClock The new clock time point to compare with the stored clock.
     * @param bUpdateEntities A boolean reference that will be set to true if entities are updated.
     */
    void UpdateLevel(std::chrono::system_clock::time_point newClock, bool &bUpdateEntities)
    {
        while (std::chrono::duration_cast<std::chrono::milliseconds>(newClock - _clock).count() >
            100) {
            bUpdateEntities = true;
            // make position copy
            if (auto positionsBefore = _componentManager.getComponentMap<PositionComponent>()) {
                std::unordered_map<int, PositionComponent> previousPositions;
                // Save previous positions
                for (auto &pair : **positionsBefore) {
                    int entityId = pair.first;
                    auto positionComponent = pair.second;
                    auto position = std::any_cast<PositionComponent>(&positionComponent);
                    if (position) {
                        previousPositions.insert({entityId, *position});
                    }
                }
                // Move entities
                _moveSystem->moveEntities(_componentManager, _entityManager);
                // Compare new positions
                if (auto positionsAfter = _componentManager.getComponentMap<PositionComponent>()) {
                    for (auto &pair : **positionsAfter) {
                        int entityId = pair.first;
                        auto &newPositionComponent = pair.second;
                        if (auto newPosition =
                                std::any_cast<PositionComponent>(&newPositionComponent)) {
                            auto it = previousPositions.find(entityId);
                            if (it != previousPositions.end()) {
                                auto &oldPosition = it->second;
                                if (oldPosition.x != newPosition->x ||
                                    oldPosition.y != newPosition->y) {
                                    if (auto spriteData =
                                            _componentManager.getComponent<SpriteDataComponent>(
                                                entityId)) {
                                        r_type::net::Message<TypeMessage> msg;
                                        vf2d newPos(newPosition->x, newPosition->y);
                                        msg.header.id = TypeMessage::MoveEntityMessage;
                                        msg << entityId << newPos;
                                        // msg << FormatEntityInformation(
                                        //     _entityManager.getEntity(entityId).value()->getId());
                                        MessageAllClients(msg);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Collision system
            std::vector<int> entitiesToRemove;
            auto beforeCollisioneEntities = _entityManager.getAllEntities();
            for (size_t i = 0; i < beforeCollisioneEntities.size(); ++i) {
                int entityId1 = beforeCollisioneEntities[i].getId();
                for (size_t j = i + 1; j < beforeCollisioneEntities.size(); ++j) {
                    int entityId2 = beforeCollisioneEntities[j].getId();
                    if (_collisionSystem->checkCollision(
                            _componentManager, entityId1, entityId2)) {
                        auto shooterEnemy1 =
                            _componentManager.getComponent<ShootComponent>(entityId1);
                        auto enemyMissile1 =
                            _componentManager.getComponent<EnemyMissileComponent>(entityId1);
                        auto basicMonster1 =
                            _componentManager.getComponent<BasicMonsterComponent>(entityId1);
                        auto shooterEnemy2 =
                            _componentManager.getComponent<ShootComponent>(entityId2);
                        auto enemyMissile2 =
                            _componentManager.getComponent<EnemyMissileComponent>(entityId2);
                        auto basicMonster2 =
                            _componentManager.getComponent<BasicMonsterComponent>(entityId2);
                        if (auto player1 =
                                _componentManager.getComponent<PlayerComponent>(entityId1)) {
                            if (auto playerHealth =
                                    _componentManager.getComponent<HealthComponent>(entityId1)) {
                                if (shooterEnemy2 || enemyMissile2) {
                                    if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                            entityId2) == entitiesToRemove.end()) {
                                        entitiesToRemove.push_back(entityId2);
                                    }
                                    playerHealth.value()->health -= 1;
                                }
                                if (basicMonster2) {
                                    playerHealth.value()->health -= 1;
                                }
                                if (playerHealth.value()->health <= 0) {
                                    if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                            entityId1) == entitiesToRemove.end()) {
                                        entitiesToRemove.push_back(entityId1);
                                    }
                                }
                            }
                        } else if (auto playerMissile1 =
                                       _componentManager.getComponent<PlayerMissileComponent>(
                                           entityId1)) {
                            if (shooterEnemy2 || enemyMissile2 || basicMonster2) {
                                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                        entityId1) == entitiesToRemove.end()) {
                                    entitiesToRemove.push_back(entityId1);
                                }
                                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                        entityId2) == entitiesToRemove.end()) {
                                    entitiesToRemove.push_back(entityId2);
                                }
                            }
                        } else if (auto player2 = _componentManager.getComponent<PlayerComponent>(
                                       entityId2)) {
                            if (auto playerHealth =
                                    _componentManager.getComponent<HealthComponent>(entityId2)) {
                                if (shooterEnemy1 || enemyMissile1) {
                                    if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                            entityId1) == entitiesToRemove.end()) {
                                        entitiesToRemove.push_back(entityId1);
                                    }
                                    playerHealth.value()->health -= 1;
                                }
                                if (basicMonster1) {
                                    playerHealth.value()->health -= 1;
                                }
                                if (playerHealth.value()->health <= 0) {
                                    if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                            entityId2) == entitiesToRemove.end()) {
                                        entitiesToRemove.push_back(entityId2);
                                    }
                                }
                            }
                        } else if (auto playerMissile2 =
                                       _componentManager.getComponent<PlayerMissileComponent>(
                                           entityId2)) {
                            if (shooterEnemy1 || enemyMissile1 || basicMonster1) {
                                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                        entityId1) == entitiesToRemove.end()) {
                                    entitiesToRemove.push_back(entityId1);
                                }
                                if (std::find(entitiesToRemove.begin(), entitiesToRemove.end(),
                                        entityId2) == entitiesToRemove.end()) {
                                    entitiesToRemove.push_back(entityId2);
                                }
                            }
                        } else {
                            continue;
                        }
                    }
                }
            }
            for (int entityId : entitiesToRemove) {
                r_type::net::Message<TypeMessage> msg;
                msg.header.id = TypeMessage::DestroyEntityMessage;
                msg << entityId;
                MessageAllClients(msg);
                _componentManager.removeEntityFromAllComponents(entityId);
                _entityManager.removeEntity(entityId);
            }
            // Remove entities when they go off-screen
            auto afterCollisionEntities = _entityManager.getAllEntities();
            for (const auto &entity : afterCollisionEntities) {
                int entityId = entity.getId();
                if (_collisionSystem->checkOffScreen(_componentManager, entityId)) {
                    r_type::net::Message<TypeMessage> msg;
                    msg.header.id = TypeMessage::DestroyEntityMessage;
                    msg << entityId;
                    MessageAllClients(msg);
                    _componentManager.removeEntityFromAllComponents(entityId);
                    _entityManager.removeEntity(entityId);
                }
            }

            // Animation system
            if (auto animationsBefore = _componentManager.getComponentMap<AnimationComponent>()) {

                std::unordered_map<int, AnimationComponent> previousAnimations;

                // Save previous animations
                for (const auto &pair : **animationsBefore) {
                    int entityId = pair.first;
                    const auto animationComponent = pair.second;
                    auto animation = std::any_cast<AnimationComponent>(&animationComponent);
                    if (animation) {
                        previousAnimations.insert({entityId, *animation});
                    }
                }
                _animationSystem->AnimationEntities(_componentManager, _entityManager, 0.5);
                // Compare new Animations
                if (auto animationsAfter =
                        _componentManager.getComponentMap<AnimationComponent>()) {
                    for (const auto &pair : **animationsAfter) {
                        int entityId = pair.first;
                        const auto &newAnimationComponent = pair.second;
                        auto newAnimation =
                            std::any_cast<AnimationComponent>(&newAnimationComponent);
                        if (newAnimation) {
                            auto it = previousAnimations.find(entityId);
                            if (it != previousAnimations.end()) {
                                const auto &oldAnimation = it->second;
                                if (oldAnimation != *newAnimation) {
                                    r_type::net::Message<TypeMessage> msg;
                                    msg.header.id = TypeMessage::AnimateEntityMessage;
                                    msg << entityId << newAnimation->dimension
                                        << newAnimation->offset;
                                    MessageAllClients(msg);
                                }
                            }
                        }
                    }
                }
            }

            // auto fire system
            _autoFireSystem->handleAutoFire(_componentManager, _entityManager);
            auto shootComponentMap = _componentManager.getComponentMap<ShootComponent>();
            if (shootComponentMap) {
                for (auto &pair : **shootComponentMap) {
                    int entityId = pair.first;
                    auto &shootComponent = pair.second;
                    if (auto shootInfo = std::any_cast<ShootComponent>(&shootComponent)) {
                        if (shootInfo->canShoot) {
                            r_type::net::Message<TypeMessage> enemyMissileMsg;
                            enemyMissileMsg.header.id = TypeMessage::CreateEntityMessage;
                            enemyMissileMsg << InitiateEnemyMissile(entityId);
                            MessageAllClients(enemyMissileMsg);
                            shootInfo->canShoot = false;
                        }
                    }
                }
            }
            _clock += std::chrono::milliseconds(100);
        }
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
        if (_nbrOfPlayers == 0)
            return;
        if (_nbrOfPlayers > 0 && !_playerConnected) {
            _playerConnected = true;
            _clock = std::chrono::system_clock::now();
        }

        bool bUpdateEntities = false;
        std::chrono::system_clock::time_point newClock = std::chrono::system_clock::now();
        std::thread levelUpdate([this, newClock, &bUpdateEntities]() {
            this->UpdateLevel(newClock, bUpdateEntities);
        });

        size_t nMessageCount = 0;
        while (nMessageCount < nMaxMessages && !_qMessagesIn.empty()) {
            auto msg = _qMessagesIn.pop_front();

            OnMessage(msg.remote, msg.msg);

            nMessageCount++;
        }
        levelUpdate.join();
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

    void UpdatePlayerPosition(vf2d entityPosition, uint32_t entityId) // Only for the players
    {
        auto entitySpriteData = _componentManager.getComponent<SpriteDataComponent>(entityId);
        EntityInformation entity;

        auto hitbox = _componentManager.getComponent<HitboxComponent>(entityId);

        if (hitbox) {
            float halfWidth = hitbox.value()->w / 2;
            float halfHeight = hitbox.value()->h / 2;
            float minX, maxX, minY, maxY;

            maxX = ((entityPosition.x / 100) * SCREEN_WIDTH) + halfWidth;
            minX = ((entityPosition.x / 100) * SCREEN_WIDTH) - halfWidth;
            maxY = ((entityPosition.y / 100) * SCREEN_HEIGHT) + halfHeight;
            minY = ((entityPosition.y / 100) * SCREEN_HEIGHT) - halfHeight;

            if (maxX > SCREEN_WIDTH || minX < 0 || maxY > (SCREEN_HEIGHT - 30) || minY < 0) {
                return;
            }
            auto pos = _componentManager.getComponent<PositionComponent>(entityId);
            auto vel = _componentManager.getComponent<VelocityComponent>(entityId);
            if (pos && vel) {
                // player go down
                if (pos.value()->y < entityPosition.y) {
                    vel.value()->y -= 0.1;
                    if (vel.value()->y < -1) {
                        vel.value()->y = -1;
                    }
                } else if (pos.value()->y > entityPosition.y) {
                    vel.value()->y += 0.1;
                    if (vel.value()->y > 1) {
                        vel.value()->y = 1;
                    }
                }
                pos.value()->x = entityPosition.x;
                pos.value()->y = entityPosition.y;
            }

            // Update entity information and send to all clients
            uint32_t id = entityId;
            vf2d newPos = entityPosition;
            std::cout << "id: " << id << std::endl;
            std::cout << "New position: " << newPos.x << " " << newPos.y << std::endl;
            entity.spriteData = *entitySpriteData.value();
            r_type::net::Message<TypeMessage> moveMsg;
            moveMsg.header.id = TypeMessage::MoveEntityMessage;
            moveMsg << id << newPos;
            MessageAllClients(moveMsg);
        }
    }

    /**
     * @brief Retrieves the entity ID associated with a client ID.
     *
     * @param id The client ID.
     * @return uint32_t The entity ID associated with the client.
     */
    uint32_t GetClientPlayerId(uint32_t id) { return _clientPlayerID[id]; }

    uint32_t GetPlayerClientId(uint32_t id)
    {
        for (const auto &pair : _clientPlayerID) {
            if (pair.second == id) {
                return pair.first;
            }
        }
        throw std::runtime_error("Player ID not found");
    }

    /**
     * @brief Removes a player from the game based on the client ID.
     *
     * @param id The client ID of the player to be removed.
     */
    void RemovePlayer(uint32_t id) { _clientPlayerID.erase(id); }

    /**
     * @brief Removes entities associated with a player.
     *
     * @param id The ID of the player whose entities are to be removed.
     */
    void RemoveEntity(uint32_t id)
    {
        if (auto entity = _entityManager.getEntity(id)) {
            _componentManager.removeEntityFromAllComponents(id);
            _entityManager.removeEntity(id);
        }
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
        auto playerHealth = _componentManager.getComponent<HealthComponent>(entityInfo.uniqueID);
        if (playerSprite && playerPos && animation && playerHealth) {
            entityInfo.ratio.x =
                (animation.value()->dimension.x * playerSprite.value()->scale.x) / SCREEN_WIDTH;
            entityInfo.ratio.y =
                (animation.value()->dimension.y * playerSprite.value()->scale.y) / SCREEN_HEIGHT;
            entityInfo.spriteData = *(playerSprite.value());
            entityInfo.vPos.x = playerPos.value()->x;
            entityInfo.vPos.y = playerPos.value()->y;
            entityInfo.animationComponent.dimension = animation.value()->dimension;
            entityInfo.animationComponent.offset = animation.value()->offset;
            entityInfo.life = playerHealth.value()->health;
        }
        _clientPlayerID.insert_or_assign(clientId, entityInfo.uniqueID);
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
        auto entityHealth = _componentManager.getComponent<HealthComponent>(entityId);
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
            if (entityHealth) {
                entityInfo.life = entityHealth.value()->health;
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
    EntityInformation InitiatePlayerMissile(int clientId)
    {
        EntityInformation entityInfo;
        uint32_t playerId = GetClientPlayerId(clientId);
        Entity missile =
            _entityFactory.createPlayerMissile(_entityManager, _componentManager, playerId);
        entityInfo.uniqueID = missile.getId();
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

    /**
     * @brief Initializes a background entity.
     *
     * The function creates and returns information about the background entity.
     *
     * @return EntityInformation The information of the background entity.
     */
    EntityInformation InitiateBackground()
    {
        EntityInformation entityInfo;
        Entity background = _entityFactory.createBackground(_entityManager, _componentManager);
        entityInfo.uniqueID = background.getId();
        auto sprite = _componentManager.getComponent<SpriteDataComponent>(entityInfo.uniqueID);
        auto backgroundPos =
            _componentManager.getComponent<PositionComponent>(entityInfo.uniqueID);
        auto animation = _componentManager.getComponent<AnimationComponent>(entityInfo.uniqueID);
        if (sprite) {
            entityInfo.spriteData = *(sprite.value());
            entityInfo.vPos.x = backgroundPos.value()->x;
            entityInfo.vPos.y = backgroundPos.value()->y;
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
     * @brief Callback function that is called when a client has been successfully
     * validated.
     *
     * This function is intended to be overridden by derived classes to handle any
     * specific actions that need to be taken when a client is validated.
     *
     * @param client A shared pointer to the validated client connection.
     */
    virtual void OnClientValidated(std::shared_ptr<Connection<T>> client) {}

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

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::shared_ptr<MoveSystem> _moveSystem;
    std::shared_ptr<CollisionSystem> _collisionSystem;
    std::shared_ptr<AnimationSystem> _animationSystem;
    std::shared_ptr<AutoFireSystem> _autoFireSystem;

    /**
     * @brief A container that maps client IDs to player IDs.
     *
     * left: client ID
     * right: player ID
     *
     * This unordered map is used to associate client IDs with their corresponding player
     * IDs. The keys are o}f type uint32_t representing the client IDs, and the values are
     * also of type uint32_t representing the player IDs.
     */
    std::unordered_map<uint32_t, uint32_t> _clientPlayerID;

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

    /**
     * @brief
     *
     */
};
} // namespace net
} // namespace r_type