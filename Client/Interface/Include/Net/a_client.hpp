/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netClient
*/

#pragma once

#include "i_client.hpp"
#include <entity_struct.hpp>
#include <unordered_map>

namespace r_type {
namespace net {
template <typename T> class AClient : virtual public IClient<T> {
  public:
    AClient() {}

    virtual ~AClient() { Disconnect(); }

  public:
    /**
     * @brief Connects to a remote host using UDP protocol.
     *
     * @param host The IP address or hostname of the remote host.
     * @param port The port number of the remote host.
     * @return true if the connection is successful, false otherwise.
     */
    bool Connect(const std::string &host, const uint16_t port)
    {
        try {
            asio::ip::udp::endpoint remote_endpoint =
                asio::ip::udp::endpoint(asio::ip::address::from_string(host), port);
            // std::cout << "Remote endpoint: " << remote_endpoint << std::endl;

            asio::ip::udp::socket socket(
                m_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));
            m_connection = std::make_unique<Connection<T>>(Connection<T>::owner::client, m_context,
                std::move(socket), std::move(remote_endpoint), m_qMessagesIn);
            m_connection->ConnectToServer();

            // std::cout << "Connection: " << *(m_connection.get()) << std::endl;

            thrContext = std::thread([this]() { m_context.run(); });
        } catch (std::exception &e) {
            std::cerr << "Client Exception: " << e.what() << std::endl;
            return false;
        }
        return true;
    }

    /**
     * @brief Disconnects the client from the server.
     *
     * This function disconnects the client from the server if it is currently connected.
     * It stops the context and joins the context thread.
     * It also releases the connection resource.
     */
    void Disconnect()
    {
        if (IsConnected()) {
            m_connection->Disconnect();
        }

        m_context.stop();
        if (thrContext.joinable())
            thrContext.join();

        m_connection.release();
    }

    /**
     * @brief Checks if the client is connected to the server.
     *
     * @return true
     * @return false
     */
    bool IsConnected()
    {
        if (m_connection)
            return m_connection->IsConnected();
        else
            return false;
    }

    /**
     * @brief Add a new entity to the list of entities
     *
     * @param entity
     */
    void AddEntity(EntityInformation entity)
    {
        Entities.insert_or_assign(entity.uniqueID, entity);
    }

    /**
     * @brief Remove an entity from the list of entities
     *
     * @param id
     */
    void RemoveEntity(uint32_t id) {
        Entities.erase(id);
    }

    /**
     * @brief This function updates the information of an entity. If the entity does not exist in the collection of entities, it will be added. Otherwise, the existing entity will be updated with the new information.
     *
     * @param entity The entity information to be updated.
     */
    void UpdateEntity(EntityInformation entity)
    {
        if (Entities.find(entity.uniqueID) == Entities.end())
            AddEntity(entity);
        Entities[entity.uniqueID] = entity;
    }

    /**
     * @brief Get the Players object
     *
     * @return std::unordered_map<uint32_t, EntityInformation>
     */
    std::unordered_map<uint32_t, EntityInformation> GetPlayers() { return Entities; }

    /**
     * @brief Get a player by its id
     *
     * @param id
     * @return EntityInformation
     */
    EntityInformation GetAPlayer(uint32_t id) { return Entities[id]; }

    void SetEntityID(int id) { EntityID = id; }
    int GetEntityID() { return EntityID; }

  public:
    /**
     * @brief Send message to server
     *
     * @param msg
     */
    void Send(const Message<T> &msg)
    {
        if (IsConnected())
            m_connection->Send(msg);
    }

    /**
     * @brief get incoming messages
     *
     * @return ThreadSafeQueue<OwnedMessage<T>>&
     */
    ThreadSafeQueue<OwnedMessage<T>> &Incoming() { return m_qMessagesIn; }

    const std::unique_ptr<Connection<T>> &getConnection() { return m_connection; }

  protected:
    asio::io_context m_context;
    std::thread thrContext;
    std::unique_ptr<Connection<T>> m_connection;

  private:
    ThreadSafeQueue<OwnedMessage<T>> m_qMessagesIn;
    std::unordered_map<uint32_t, EntityInformation> Entities;
    int EntityID = 0;
};
} // namespace net
} // namespace r_type