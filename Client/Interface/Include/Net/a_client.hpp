/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netClient
*/

#pragma once

#include <Components/component_manager.hpp>
#include <Components/components.hpp>
#include <Net/i_client.hpp>
#include <entity_struct.hpp>
#include <texture_manager.hpp>
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
                asio::ip::udp::endpoint(asio::ip::make_address(host), port);
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

    void setPlayerId(int id) { playerId = id; }
    uint32_t getPlayerId() { return playerId; }

    void addEntity(EntityInformation entity, ComponentManager &componentManager,
        TextureManager &textureManager, sf::Vector2u windowSize);
    void updateEntity(
        EntityInformation entity, ComponentManager &componentManager, sf::Vector2u windowSize);
    void removeEntity(int entityId, ComponentManager &componentManager);

  protected:
    asio::io_context m_context;
    std::thread thrContext;
    std::unique_ptr<Connection<T>> m_connection;

  private:
    ThreadSafeQueue<OwnedMessage<T>> m_qMessagesIn;
    uint32_t playerId = 0;
};
} // namespace net
} // namespace r_type