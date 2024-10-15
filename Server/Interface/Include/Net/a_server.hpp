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
#include <cmath>
#include <entity_struct.hpp>
#include <unordered_map>

namespace r_type {
namespace net {
/**
 * @brief AServer class
 *
 * @param T
 */
template <typename T> class AServer : virtual public r_type::net::IServer<T> {
  public:
    /**
     * @brief Construct a new Server Interface object
     *
     * @param port
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
     * @brief Destroy the Server Interface object
     *
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
     * @brief send message message to client
     *
     * @param client
     * @param msg
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
     * @brief message all clients
     *
     * @param msg
     * @param pIgnoreClient
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
     * @brief update server
     *
     * @param nMaxMessages
     * @param bWait
     */
    void Update(size_t nMaxMessages = -1, bool bWait = false)
    {
        if (bWait)
            m_qMessagesIn.wait();
        std::chrono::system_clock::time_point newClock = std::chrono::system_clock::now();
        // std::cout
        //     << "Time: "
        //     << std::chrono::duration_cast<std::chrono::milliseconds>(newClock - _clock).count()
        //     << std::endl;
        while (std::chrono::duration_cast<std::chrono::milliseconds>(newClock - _clock).count() >
            100) {

            const std::vector<Entity> entities = entityManager.getAllEntities();
            for (const auto &entity : entities) {
                getCompo
                if (entity.getId() != entityID && entity.getId() != 1) {
                }
            }
        }
        newClock -= std::chrono::milliseconds(100);
        _clock = newClock;

        size_t nMessageCount = 0;
        while (nMessageCount < nMaxMessages && !m_qMessagesIn.empty()) {
            auto msg = m_qMessagesIn.pop_front();

            OnMessage(msg.remote, msg.msg);

            nMessageCount++;
        }
    }

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
        uint32_t entityTouched = CheckPlayerPosition(entity);

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

    uint32_t GetClientEntityId(uint32_t id) { return clientPlayerID[id]; }

    void RemovePlayer(uint32_t id) { clientPlayerID.erase(id); }
    void RemoveEntities(uint32_t id) { entityManager.removeEntity(id); }

    EntityInformation InitiatePlayers(int clientId)
    {
        EntityInformation entityInfo;
        Entity player = entityFactory.createPlayer(entityManager, componentManager);
        entityInfo.uniqueID = player.getId();
        entityInfo.vPos = {100, static_cast<float>(rand() % 600)};
        auto sprite = componentManager.getComponent<SpriteDataComponent>(entityInfo.uniqueID);
        if (sprite) {
            if (nbrOfPlayers == 1)
                sprite.value()->spritePath = SpritePath::Ship2;
            else if (nbrOfPlayers == 2)
                sprite.value()->spritePath = SpritePath::Ship3;
            else if (nbrOfPlayers == 3)
                sprite.value()->spritePath = SpritePath::Ship4;
            entityInfo.spriteData = *(sprite.value());
        }
        while (CheckPlayerPosition(entityInfo) != -1) {
            entityInfo.vPos = {100, static_cast<float>(rand() % 600)};
        }
        auto playerPos = componentManager.getComponent<PositionComponent>(entityInfo.uniqueID);
        if (playerPos) {
            playerPos.value()->x = entityInfo.vPos.x;
            playerPos.value()->y = entityInfo.vPos.y;
        }
        clientPlayerID.insert_or_assign(
            nIDCounter, entityInfo.uniqueID); // Assuming clientPlayerID is a
                                              // std::unordered_map<uint32_t, uint32_t> or similar.
        return entityInfo;
    }

    EntityInformation InitiateMissile(int clientId)
    {
        EntityInformation entityInfo;
        Entity missile = entityFactory.createPlayerMissile(entityManager, componentManager);
        entityInfo.uniqueID = missile.getId();
        auto playerPos =
            componentManager.getComponent<PositionComponent>(GetClientEntityId(clientId)).value();
        entityInfo.vPos.x = playerPos->x + 150;
        entityInfo.vPos.y = playerPos->y + 70;
        auto sprite = componentManager.getComponent<SpriteDataComponent>(entityInfo.uniqueID);
        if (sprite) {
            entityInfo.spriteData = *(sprite.value());
        }
        return entityInfo;
    }

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

    void InitListEntities(std::shared_ptr<r_type::net::Connection<T>> client, u_int32_t entityID)
    {
        EntityInformation entityInfo;
        r_type::net::Message<T> msgAddPlayer;
        msgAddPlayer.header.id = T::CreateEntityMessage;
        const std::vector<Entity> entities = entityManager.getAllEntities();
        for (const auto &entity : entities) {
            if (entity.getId() != entityID && entity.getId() != 1) {
                auto playerPos = componentManager.getComponent<PositionComponent>(entity.getId());
                auto sprite = componentManager.getComponent<SpriteDataComponent>(entity.getId());
                if (playerPos && sprite) {
                    entityInfo.uniqueID = entity.getId();
                    entityInfo.vPos.x = playerPos.value()->x;
                    entityInfo.vPos.y = playerPos.value()->y;
                    entityInfo.spriteData = *(sprite.value());
                    msgAddPlayer << entityInfo;
                    MessageClient(client, msgAddPlayer);
                }
            }
        }
        msgAddPlayer.header.id = T::FinishInitialization;
        MessageClient(client, msgAddPlayer);
    }

    /**
     * @brief check player position to avoid collision
     *
     * @param desc
     * @return true
     * @return false
     */
    int CheckPlayerPosition(EntityInformation desc)
    {
        float descLeft, descRight, descTop, descBottom, playerLeft, playerRight, playerTop,
            playerBottom;
        const std::vector<Entity> entities = entityManager.getAllEntities();

        for (const auto &entity : entities) {
            if (entity.getId() != desc.uniqueID && entity.getId() != background.uniqueID) {
                auto playerPos = componentManager.getComponent<PositionComponent>(entity.getId());
                auto playerHitbox = componentManager.getComponent<HitboxComponent>(entity.getId());
                if (playerPos && playerHitbox) {

                    descLeft = desc.vPos.x - (desc.spriteData.dimension.x / 2);
                    descRight = desc.vPos.x + (desc.spriteData.dimension.x / 2);
                    descTop = desc.vPos.y - (desc.spriteData.dimension.y / 2);
                    descBottom = desc.vPos.y + (desc.spriteData.dimension.y / 2);

                    playerLeft = playerPos.value()->x - (playerHitbox.value()->w / 2);
                    playerRight = playerPos.value()->x + (playerHitbox.value()->w / 2);
                    playerTop = playerPos.value()->y - (playerHitbox.value()->h / 2);
                    playerBottom = playerPos.value()->y + (playerHitbox.value()->h / 2);

                    if (!(descRight < playerLeft || descLeft > playerRight ||
                            descBottom < playerTop || descTop > playerBottom)) {
                        return entity.getId();
                    }
                }
            }
        }
        return -1;
    }

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
    ThreadSafeQueue<OwnedMessage<T>> m_qMessagesIn;

    std::deque<std::shared_ptr<Connection<T>>> m_deqConnections;

    asio::io_context m_asioContext;
    std::thread m_threadContext;

    asio::ip::udp::socket m_asioSocket;
    asio::ip::udp::endpoint m_clientEndpoint;

    std::array<uint8_t, 1024> m_tempBuffer;

    uint32_t nIDCounter = 10000;

    ComponentManager componentManager;
    EntityManager entityManager;
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

    int nbrOfPlayers = 0;

    std::chrono::system_clock::time_point _clock = std::chrono::system_clock::now();

    EntityInformation background;
};
} // namespace net
} // namespace r_type