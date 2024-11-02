/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#pragma once

#include "a_server.hpp"

namespace r_type {
namespace net {
/**
 * @class Server
 * @brief A server class that handles client connections and messaging.
 *
 * This class inherits from r_type::net::AServer<TypeMessage> and provides
 * implementations for handling client connections, disconnections, and
 * message reception.
 *
 * @tparam TypeMessage The type of message that the server will handle.
 */
class Server : virtual public r_type::net::AServer<TypeMessage> {
  public:
    /**
     * @brief Constructs a new Server object with the specified port number.
     *
     * This constructor initializes the Server object by calling the constructors
     * of the base classes r_type::net::IServer<TypeMessage> and
     * r_type::net::AServer<TypeMessage> with the provided port number.
     *
     * @param nPort The port number on which the server will listen for incoming connections.
     */
    Server(uint16_t nPort)
        : r_type::net::IServer<TypeMessage>(), r_type::net::AServer<TypeMessage>(nPort)
    {
    }

    /**
     * @brief Destructor for the Server class.
     *
     * This destructor is responsible for cleaning up any resources
     * allocated by the Server class. Currently, it does not perform
     * any specific actions.
     */
    ~Server() {}

  protected:

    /**
     * @brief Handles the event when a client attempts to connect to the server.
     *
     * @param client A shared pointer to the client's connection object.
     * @return true if the client is allowed to connect, false otherwise.
     */
    bool OnClientConnect(std::shared_ptr<r_type::net::Connection<TypeMessage>> client);

    /**
     * @brief Handles the event when a client disconnects from the server.
     *
     * @param client A shared pointer to the client's connection object.
     * @param msg A reference to the message object containing information about the disconnection.
     */
    void OnClientDisconnect(std::shared_ptr<r_type::net::Connection<TypeMessage>> client,
        r_type::net::Message<TypeMessage> &msg);


    /**
     * @brief Handles incoming messages from a client.
     *
     * This function is called whenever a message is received from a client.
     * It processes the message and performs the necessary actions based on
     * the message content.
     *
     * @param client A shared pointer to the client connection that sent the message.
     * @param msg The message received from the client.
     */
    void OnMessage(std::shared_ptr<r_type::net::Connection<TypeMessage>> client,
        r_type::net::Message<TypeMessage> &msg);
};
} // namespace net
} // namespace r_type
