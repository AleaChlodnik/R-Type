/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** simpleClient
*/

#pragma once

#include "net_a_client.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace r_type {
namespace net {
class Client : virtual public r_type::net::AClient<NetR_TypeMessage> {
  public:
    void PingServer()
    {
        r_type::net::Message<NetR_TypeMessage> msg;
        msg.header.id = NetR_TypeMessage::ServerPing;

        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

        msg << timeNow;
        Send(msg);
    }

    void MessageAll()
    {
        r_type::net::Message<NetR_TypeMessage> msg;
        msg.header.id = NetR_TypeMessage::MessageAll;
        Send(msg);
    }
};
} // namespace net
} // namespace r_type
