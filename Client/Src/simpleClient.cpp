/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** simpleClient
*/

#include <iostream>
#include <olcNet.hpp>

enum class CustomMsgTypes : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage,
};

class CustomClient : public olc::net::ClientInterface<CustomMsgTypes> {
  public:
    // void PingServer()
    // {
    //     olc::net::message<CustomMsgTypes> msg;
    //     msg.header.id = CustomMsgTypes::ServerPing;

    //     // Caution with this...
    //     std::chrono::system_clock::time_point timeNow =
    //         std::chrono::system_clock::now();

    //     msg << timeNow;
    //     Send(msg);
    // }

    // void MessageAll()
    // {
    //     olc::net::message<CustomMsgTypes> msg;
    //     msg.header.id = CustomMsgTypes::MessageAll;
    //     Send(msg);
    // }
};

void simpleClient()
{
    CustomClient c;
    c.Connect("127.0.0.1", 60000);
}
