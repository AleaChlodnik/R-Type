/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** simpleClient
*/

#include "netCommon.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <olcNet.hpp>

/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** netClient
*/

#pragma once
#include "netCommon.hpp"
#include "netConnection.hpp"
#include "netThreadSafeQueue.hpp"

#include <unordered_map>

namespace olc {
namespace net {
class CustomClient : public olc::net::ClientInterface<CustomMsgTypes> {
  public:
    void PingServer()
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerPing;

        std::chrono::system_clock::time_point timeNow =
            std::chrono::system_clock::now();

        msg << timeNow;
        Send(msg);
    }

    void MessageAll()
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::MessageAll;
        Send(msg);
    }

    void UpdatePlayerInformation(sPlayerInformation desc)
    {
        if (Players.find(desc.nUniqueID) == Players.end())
            AddPlayer(desc);
        Players[desc.nUniqueID] = desc;
    }

    void AddPlayer(sPlayerInformation desc)
    {
        Players.insert_or_assign(desc.nUniqueID, desc);
    }

    void GameServerInformaton(olc::net::message<CustomMsgTypes> &msg)
    {
        switch (msg.header.id) {
        case CustomMsgTypes::Game_UpdateEntity: {
            sPlayerInformation desc;
            msg >> desc;
        } break;
        }
        return;
    }

    std::unordered_map<uint32_t, sPlayerInformation> getPlayers()
    {
        return Players;
    }
    sPlayerInformation GetAPlayer(uint32_t id) { return Players[id]; }

    void SetPlayerID(uint32_t id) { nPlayerID = id; }
    uint32_t GetPlayerID() { return nPlayerID; }

  protected:
    asio::io_context m_context;
    std::thread thrContext;
    std::unique_ptr<Connection<CustomMsgTypes>> m_connection;

  private:
    uint32_t nPlayerID;
    std::unordered_map<uint32_t, sPlayerInformation> Players;

    ThreadSafeQueue<owned_message<CustomMsgTypes>> m_qMessagesIn;

    bool bWaitingForConnection = true;

  public:
};
} // namespace net
} // namespace olc

void simpleClient()
{
    olc::net::CustomClient c;
    srand(time(NULL));
    c.Connect("127.0.0.1", 60000);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Preferences");
    sf::Event event;

    auto updatePlayerPosition = [&](const olc::vf2d &delta) {
        sPlayerInformation desc = c.GetAPlayer(c.GetPlayerID());
        olc::net::message<CustomMsgTypes> msg;
        desc.vPos.x += delta.x;
        desc.vPos.y += delta.y;
        msg.header.id = CustomMsgTypes::Game_UpdatePositionEntity;
        msg << desc;
        c.Send(msg);
    };

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    updatePlayerPosition(olc::vf2d(0, -5));
                    break;
                case sf::Keyboard::Down:
                    updatePlayerPosition(olc::vf2d(0, 5));
                    break;
                case sf::Keyboard::Left:
                    updatePlayerPosition(olc::vf2d(-5, 0));
                    break;
                case sf::Keyboard::Right:
                    updatePlayerPosition(olc::vf2d(5, 0));
                    break;
                default:
                    break;
                }
            }
        }

        if (c.IsConnected()) {
            if (!c.Incoming().empty()) {
                auto msg = c.Incoming().pop_front().msg;

                switch (msg.header.id) {
                case CustomMsgTypes::ServerAccept: {
                    sPlayerInformation desc;
                    msg >> desc;
                    c.AddPlayer(desc);
                    c.SetPlayerID(desc.nUniqueID);
                    break;
                }
                case CustomMsgTypes::ServerPing: {
                    auto timeNow = std::chrono::system_clock::now();
                    std::chrono::system_clock::time_point timeThen;
                    msg >> timeThen;
                    std::cout
                        << "Ping: "
                        << std::chrono::duration<double>(timeNow - timeThen)
                               .count()
                        << std::endl;
                    break;
                }
                case CustomMsgTypes::ServerMessage: {
                    uint32_t clientID;
                    msg >> clientID;
                    std::cout << "Hello from [" << clientID << "]"
                              << std::endl;
                    break;
                }
                case CustomMsgTypes::ServerDeny: {
                    break;
                }
                case CustomMsgTypes::Game_UpdateEntity: {
                    sPlayerInformation desc;
                    msg >> desc;
                    c.UpdatePlayerInformation(desc);

                    olc::net::message<CustomMsgTypes> response;
                    response.header.id = CustomMsgTypes::Client_EntityReceveid;
                    c.Send(response);
                    break;
                }
                case CustomMsgTypes::Game_AddEntity: {
                    sPlayerInformation desc;
                    msg >> desc;
                    c.AddPlayer(desc);

                    olc::net::message<CustomMsgTypes> response;
                    response.header.id = CustomMsgTypes::Client_EntityReceveid;
                    c.Send(response);
                    break;
                }
                }
            }

            window.clear();
            for (const auto &player : c.getPlayers()) {
                sf::RectangleShape carre(
                    {player.second.fRadius, player.second.fRadius});
                carre.setPosition(player.second.vPos.x, player.second.vPos.y);
                carre.setFillColor(sf::Color::White);
                window.draw(carre);
            }
            window.display();
        } else {
            std::cout << "Not Connected" << std::endl;
        }
    }
}