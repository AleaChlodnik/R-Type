/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netServer
*/

#pragma once

#include "hitbox_tmp.hpp"
#include <Components/component_manager.hpp>
#include <Components/components.hpp>
#include <Entities/entity_factory.hpp>
#include <Entities/entity_manager.hpp>
#include <Net/i_server.hpp>
#include <cmath>
#include <entity_struct.hpp>
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
          m_asioSocket(m_asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
    {
        entityManager = EntityManager();
        entityFactory = EntityFactory();
        componentManager = ComponentManager();
        background = InitiateBackground();
        entityFactory.createBasicMonster(entityManager, componentManager);
        entityFactory.createBasicMonster(entityManager, componentManager);
        entityFactory.createBasicMonster(entityManager, componentManager);
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

            m_threadContext = std::thread([this]() { m_asioContext.run(); });
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
        m_asioContext.stop();

        if (m_threadContext.joinable())
            m_threadContext.join();

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
        m_asioSocket.async_receive_from(asio::buffer(m_tempBuffer.data(), m_tempBuffer.size()),
            m_clientEndpoint, [this](std::error_code ec, std::size_t bytes_recvd) {
                if (m_clientEndpoint.protocol() != asio::ip::udp::v4())
                    return WaitForClientMessage();
                if (!ec) {
                    std::cout << "[SERVER] New Connection: " << m_clientEndpoint << std::endl;
                    // check if connection already exists
                    for (std::shared_ptr<Connection<T>> &conn : m_deqConnections) {
                        if (conn->getEndpoint() == m_clientEndpoint) {
                            std::cout << "[SERVER] Connection already exists" << std::endl;
                            return;
                        }
                    }

                    asio::ip::udp::socket m_newSocket(
                        m_asioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));

                    // create client socket
                    std::shared_ptr<Connection<T>> newConn = std::make_shared<Connection<T>>(
                        Connection<T>::owner::server, m_asioContext, std::move(m_newSocket),
                        m_clientEndpoint, m_qMessagesIn);

                    if (OnClientConnect(newConn)) {
                        m_deqConnections.push_back(std::move(newConn));
                        m_deqConnections.back()->ConnectToClient(this, nIDCounter++);
                        std::cout << "[" << m_deqConnections.back()->GetID()
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

            m_deqConnections.erase(
                std::remove(m_deqConnections.begin(), m_deqConnections.end(), client),
                m_deqConnections.end());
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

        for (auto &client : m_deqConnections) {
            if (client && client->IsConnected()) {
                if (client != pIgnoreClient)
                    client->Send(msg);
            } else {
                OnClientDisconnect(client);
                client.reset();
                bInvalidClientExists = true;
            }
        }

        if (bInvalidClientExists)
            m_deqConnections.erase(
                std::remove(m_deqConnections.begin(), m_deqConnections.end(), nullptr),
                m_deqConnections.end());
    }

    /**
     * @brief Updates the server state and processes incoming messages.
     *
     * This function updates the state of entities on the server and processes incoming messages.
     * It can optionally wait for messages and limit the number of messages processed in one call.
     *
     * @param nMaxMessages The maximum number of messages to process in one call. Default is -1 (no
     * limit).
     * @param bWait If true, the function will wait for messages to be available before processing.
     *
     * The function performs the following tasks:
     * - Updates the positions of entities based on their components.
     * - Sends updated entity information to all connected clients.
     * - Checks for collisions between player missiles and monsters, and handles entity
     * destruction.
     * - Processes incoming messages from clients.
     */
    void Update(size_t nMaxMessages = -1, bool bWait = false)
    {
        // if (bWait)
        //     m_qMessagesIn.wait();
        std::chrono::system_clock::time_point newClock = std::chrono::system_clock::now();
        // std::cout
        //     << "Time: "
        //     << std::chrono::duration_cast<std::chrono::milliseconds>(newClock - _clock).count()
        //     << std::endl;

        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::UpdateEntity;

        bool bUpdateEntities = false;
        while (std::chrono::duration_cast<std::chrono::milliseconds>(newClock - _clock).count() >
            500) {
            bUpdateEntities = true;

            const std::vector<Entity> entities = entityManager.getAllEntities();
            for (const auto &entity : entities) {
                if (entity.getId() != 1) {
                    auto monster =
                        componentManager.getComponent<BasicMonsterComponent>(entity.getId());
                    auto missile =
                        componentManager.getComponent<PlayerMissileComponent>(entity.getId());
                    auto position =
                        componentManager.getComponent<PositionComponent>(entity.getId());
                    auto spriteData =
                        componentManager.getComponent<SpriteDataComponent>(entity.getId());
                    if (monster && position && spriteData) {
                        position.value()->x -= 5;
                        MessageAllClients(
                            msg << EntityInformation{static_cast<u_int32_t>(entity.getId()),
                                *(spriteData.value()),
                                {(position.value()->x), (position.value()->y)}});
                    }
                    if (missile && position && spriteData) {
                        position.value()->x += 20;
                        EntityInformation newMissile = EntityInformation{
                            static_cast<u_int32_t>(entity.getId()), *(spriteData.value()),
                            {(position.value()->x), (position.value()->y)}};
                        int newID =
                            CheckEntityMovement(newMissile, componentManager, entityManager);
                        auto monster = componentManager.getComponent<BasicMonsterComponent>(newID);
                        if (monster) {
                            r_type::net::Message<TypeMessage> msgDestroy;
                            msgDestroy.header.id = TypeMessage::DestroyEntityMessage;
                            msgDestroy << entity.getId();
                            MessageAllClients(msgDestroy);
                            RemoveEntities(entity.getId());

                            msgDestroy << newID;
                            MessageAllClients(msgDestroy);
                            RemoveEntities(newID);
                        } else {
                            MessageAllClients(msg << newMissile);
                        }
                    }
                }
            }
            _clock += std::chrono::milliseconds(500);
        }
        if (bUpdateEntities)
            _clock = newClock;

        size_t nMessageCount = 0;
        while (nMessageCount < nMaxMessages && !m_qMessagesIn.empty()) {
            auto msg = m_qMessagesIn.pop_front();

            OnMessage(msg.remote, msg.msg);

            nMessageCount++;
        }
    }

    /**
     * @brief Updates the position of an entity based on the message received and the client ID.
     *
     * This function updates the position of an entity. If the entity is not touching any other
     * player, it updates its position and sends a message to all clients about the new position.
     * If it touches another player, a destroy message is sent to all clients.
     *
     * @param msg The message containing the new position of the entity.
     * @param clientId The ID of the client sending the update.
     */

    void UpdateEntityPosition(r_type::net::Message<T> &msg, uint32_t clientId)
    {
        uint32_t entityId = GetClientEntityId(clientId);
        EntityInformation entity;
        vf2d entityPosition;
        auto entitySprite = componentManager.getComponent<SpriteDataComponent>(entityId);
        msg >> entityPosition;
        entity.uniqueID = entityId;
        entity.vPos = entityPosition;
        entity.spriteData = *entitySprite.value();
        uint32_t entityTouched = CheckEntityMovement(entity, componentManager, entityManager);

        if (entityTouched == -1) {
            auto position = componentManager.getComponent<PositionComponent>(entityId);
            if (position) {
                position.value()->x = entityPosition.x;
                position.value()->y = entityPosition.y;
                r_type::net::Message<TypeMessage> msg;
                msg.header.id = TypeMessage::UpdateEntity;
                msg << entity;
                MessageAllClients(msg);
            }
        } else {
            r_type::net::Message<TypeMessage> msg;
            componentManager.getComponent<PlayerComponent>(entityTouched);
            if (componentManager.getComponent<PlayerComponent>(entityTouched)) {
                return;
            }
            msg.header.id = TypeMessage::DestroyEntityMessage;
            msg << entity.uniqueID;
            MessageAllClients(msg);
        }
    }

    /**
     * @brief Retrieves the entity ID associated with a client ID.
     *
     * @param id The client ID.
     * @return uint32_t The entity ID associated with the client.
     */
    uint32_t GetClientEntityId(uint32_t id) { return clientPlayerID[id]; }

    /**
     * @brief Removes a player from the game based on the client ID.
     *
     * @param id The client ID of the player to be removed.
     */
    void RemovePlayer(uint32_t id) { clientPlayerID.erase(id); }

    /**
     * @brief Removes entities associated with a player.
     *
     * @param id The ID of the player whose entities are to be removed.
     */
    void RemoveEntities(uint32_t id) { entityManager.removeEntity(id); }

    /**
     * @brief Initializes a new player entity and assigns a random position.
     *
     * The function creates a new player entity, assigns it a random position, and ensures that
     * it does not overlap with any other players.
     *
     * @param clientId The client ID of the player being initialized.
     * @return EntityInformation The information of the newly created player entity.
     */
    EntityInformation InitiatePlayers(int clientId)
    {
        EntityInformation entityInfo;
        Entity player = entityFactory.createPlayer(entityManager, componentManager, nbrOfPlayers);
        auto playerSprite =
            componentManager.getComponent<SpriteDataComponent>(entityInfo.uniqueID);
        auto playerPos = componentManager.getComponent<PositionComponent>(entityInfo.uniqueID);
        if (playerSprite && playerPos) {
            entityInfo.spriteData = *(playerSprite.value());
            entityInfo.vPos.x = playerPos.value()->x;
            entityInfo.vPos.y = playerPos.value()->y;
        }
        entityInfo.uniqueID = player.getId();
        clientPlayerID.insert_or_assign(nIDCounter, entityInfo.uniqueID);
        return entityInfo;
    }

    /**
     * @brief Initializes a missile entity associated with a player.
     *
     * The function creates a missile entity associated with a player and assigns its position
     * based on the player's current position.
     *
     * @param clientId The client ID of the player firing the missile.
     * @return EntityInformation The information of the newly created missile entity.
     */
    EntityInformation InitiateMissile(int clientId)
    {
        EntityInformation entityInfo;
        uint32_t playerId = GetClientEntityId(clientId);
        Entity missile =
            entityFactory.createPlayerMissile(entityManager, componentManager, playerId);
        auto missilePos = componentManager.getComponent<PositionComponent>(entityInfo.uniqueID);
        auto sprite = componentManager.getComponent<SpriteDataComponent>(entityInfo.uniqueID);
        if (missilePos && sprite) {
            entityInfo.vPos.x = missilePos.value()->x;
            entityInfo.vPos.y = missilePos.value()->y;
            entityInfo.spriteData = *(sprite.value());
        }
        entityInfo.uniqueID = missile.getId();
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
        Entity background = entityFactory.createBackground(entityManager, componentManager);
        entityInfo.uniqueID = background.getId();
        auto sprite = componentManager.getComponent<SpriteDataComponent>(entityInfo.uniqueID);
        if (sprite) {
            entityInfo.spriteData = *(sprite.value());
        }
        return entityInfo;
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
    virtual void InitListEntities(
        std::shared_ptr<r_type::net::Connection<T>> client, u_int32_t entityID) = 0;

    /**
     * @brief Callback function that is called when a client has been successfully validated.
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
    ThreadSafeQueue<OwnedMessage<T>> m_qMessagesIn;

    /**
     * @brief A deque that holds shared pointers to Connection objects.
     *
     * This member variable is used to manage a collection of active connections.
     * The use of std::shared_ptr ensures that the Connection objects are
     * reference-counted and automatically deallocated when no longer in use.
     *
     * @tparam T The type of data that the Connection handles.
     */
    std::deque<std::shared_ptr<Connection<T>>> m_deqConnections;

    /**
     * @brief The io_context object provides I/O services, such as sockets, that the server will
     * use.
     *
     * This member variable is responsible for managing asynchronous I/O operations.
     * It is part of the ASIO library, which is used for network programming.
     */
    asio::io_context m_asioContext;
    /**
     * @brief Thread object for managing the server's context operations.
     *
     * This member variable represents a thread that handles the server's context,
     * allowing for concurrent execution of tasks related to the server's operation.
     * It is used to ensure that the server can perform its duties without blocking
     * the main execution flow.
     */
    std::thread m_threadContext;

    /**
     * @brief A socket for sending and receiving UDP datagrams.
     *
     * This member variable represents a UDP socket using the ASIO library.
     * It is used for network communication in the server.
     */
    asio::ip::udp::socket m_asioSocket;
    /**
     * @brief Represents the endpoint of a client in a UDP connection.
     *
     * This member variable holds the endpoint information (IP address and port)
     * of a client in a UDP connection using the ASIO library.
     */
    asio::ip::udp::endpoint m_clientEndpoint;

    /**
     * @brief Temporary buffer used for storing data.
     *
     * This buffer is an array of 1024 bytes (uint8_t) used for temporary storage
     * of data within the server's network interface.
     */
    std::array<uint8_t, 1024> m_tempBuffer;

    /**
     * @brief Counter for generating unique network IDs.
     *
     * This variable is used to keep track of the current ID to be assigned
     * for network-related entities. It starts at 10000 and increments with
     * each new ID generation.
     */
    uint32_t nIDCounter = 10000;

    /**
     * @brief Manages and maintains the lifecycle of various components within the server.
     *
     * The ComponentManager is responsible for creating, updating, and destroying components
     * as needed. It ensures that all components are properly managed and that their states
     * are consistent throughout the server's operation.
     */
    ComponentManager componentManager;
    /**
     * @brief Manages the lifecycle and operations of entities within the server.
     *
     * The EntityManager is responsible for creating, updating, and deleting entities.
     * It ensures that entities are properly managed and synchronized within the server's
     * environment.
     */
    EntityManager entityManager;
    /**
     * @brief An instance of EntityFactory used to create and manage game entities.
     */
    EntityFactory entityFactory;
    /**
     * @brief A container that maps client IDs to player IDs.
     *
     * left: client ID
     * right: player ID
     *
     * This unordered map is used to associate client IDs with their corresponding player IDs.
     * The keys are o}f type uint32_t representing the client IDs, and the values are also of type
     * uint32_t representing the player IDs.
     */
    std::unordered_map<uint32_t, uint32_t> clientPlayerID;

    /**
     * @brief Number of players currently connected to the server.
     */
    int nbrOfPlayers = 0;

    /**
     * @brief Stores the current time point from the system clock.
     *
     * This variable is initialized with the current time using
     * std::chrono::system_clock::now() and represents a specific
     * point in time according to the system clock.
     */
    std::chrono::system_clock::time_point _clock = std::chrono::system_clock::now();

    /**
     * @brief Holds information about the background entity.
     *
     * This member variable stores the details related to the background entity
     * in the game. It includes properties such as position, texture, and other
     * relevant attributes that define the background's appearance and behavior.
     */
    EntityInformation background;
};
} // namespace net
} // namespace r_type