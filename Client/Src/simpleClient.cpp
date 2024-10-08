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
        std::cout << "Update Player [" << desc.nUniqueID << "] at ("
                  << desc.vPos.x << "," << desc.vPos.y << ")" << std::endl;
        if (Players.find(desc.nUniqueID) == Players.end())
            AddPlayer(desc);
        Players[desc.nUniqueID] = desc;
    }

    void AddPlayer(sPlayerInformation desc)
    {
        std::cout << "Add Player [" << desc.nUniqueID << "] at ("
                  << desc.vPos.x << "," << desc.vPos.y << ")" << std::endl;
        Players.insert_or_assign(desc.nUniqueID, desc);
        nPlayerID = desc.nUniqueID;
    }

    void GameServerInformaton(olc::net::message<CustomMsgTypes> &msg)
    {
        switch (msg.header.id) {
        case CustomMsgTypes::Game_UpdateEntity: {
            sPlayerInformation desc;
            msg >> desc;
            std::cout << "Player [" << desc.nUniqueID << "] updated at ("
                      << desc.vPos.x << "," << desc.vPos.y << ")" << std::endl;
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
    sf::RectangleShape carre(sf::Vector2f(20, 20));
    std::cout << "<------------------------Start" << std::endl;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (c.IsConnected()) {
                if (!c.Incoming().empty()) {
                    auto msg = c.Incoming().pop_front().msg;
                    switch (msg.header.id) {
                    case CustomMsgTypes::ServerAccept: {
                        sPlayerInformation desc;
                        msg >> desc;
                        c.AddPlayer(desc);
                        std::cout
                            << "Server Accepted Connection"
                            << "\nPlayer Position ["
                            << c.GetAPlayer(c.GetPlayerID()).vPos.x << ", "
                            << c.GetAPlayer(c.GetPlayerID()).vPos.y << "]"
                            << std::endl;
                    } break;

                    case CustomMsgTypes::ServerPing: {
                        std::chrono::system_clock::time_point timeNow =
                            std::chrono::system_clock::now();
                        std::chrono::system_clock::time_point timeThen;
                        msg >> timeThen;
                        std::cout << "Ping: "
                                  << std::chrono::duration<double>(
                                         timeNow - timeThen)
                                         .count()
                                  << std::endl;
                    } break;

                    case CustomMsgTypes::ServerMessage: {
                        uint32_t clientID;
                        msg >> clientID;
                        std::cout << "Hello from [" << clientID << "]"
                                  << std::endl;
                    } break;
                    case CustomMsgTypes::ServerDeny: {

                    } break;
                    case CustomMsgTypes::Game_UpdateEntity: {
                        sPlayerInformation desc;
                        msg >> desc;
                        c.UpdatePlayerInformation(desc);
                        std::cout << "Player [" << desc.nUniqueID
                                  << "] updated at ("
                                  << c.GetAPlayer(desc.nUniqueID).vPos.x << ","
                                  << c.GetAPlayer(desc.nUniqueID).vPos.y << ")"
                                  << std::endl;
                    } break;
                    case CustomMsgTypes::Game_AddEntity: {
                        sPlayerInformation desc;
                        msg >> desc;
                        c.AddPlayer(desc);
                        std::cout << "Player [" << desc.nUniqueID
                                  << "] add at ("
                                  << c.GetAPlayer(desc.nUniqueID).vPos.x << ","
                                  << c.GetAPlayer(desc.nUniqueID).vPos.y << ")"
                                  << std::endl;
                        olc::net::message<CustomMsgTypes> reponse;
                        reponse.header.id =
                            CustomMsgTypes::Client_EntityReceveid;
                        c.Send(msg);
                    }
                    }
                }
                if (event.type == sf::Event::KeyPressed) {
                    std::cout << "Key Pressed" << std::endl;
                    switch (event.key.code) {
                    case sf::Keyboard::Space: {
                        std::cout << "space" << std::endl;
                        c.PingServer();
                    } break;
                    case sf::Keyboard::Q: {
                        std::cout << "Q" << std::endl;
                        window.close();
                    } break;
                    case sf::Keyboard::V: {
                        std::cout << "V" << std::endl;
                        c.MessageAll();
                    } break;
                    case sf::Keyboard::Up: {
                        sPlayerInformation desc =
                            c.GetAPlayer(c.GetPlayerID());
                        desc.vPos.y -= 10;
                        olc::net::message<CustomMsgTypes> msg;
                        msg.header.id =
                            CustomMsgTypes::Game_UpdatePositionEntity;
                        msg << desc;
                        std::cout << "Update Player [" << desc.nUniqueID
                                  << "] at (" << desc.vPos.x << ","
                                  << desc.vPos.y << ")" << std::endl;
                        c.Send(msg);
                    } break;
                    case sf::Keyboard::Down: {
                        sPlayerInformation desc =
                            c.GetAPlayer(c.GetPlayerID());
                        desc.vPos.y += 10;
                        olc::net::message<CustomMsgTypes> msg;
                        msg.header.id =
                            CustomMsgTypes::Game_UpdatePositionEntity;
                        msg << desc;
                        std::cout << "Update Player [" << desc.nUniqueID
                                  << "] at (" << desc.vPos.x << ","
                                  << desc.vPos.y << ")" << std::endl;
                        c.Send(msg);
                    } break;
                    case sf::Keyboard::Left: {
                        sPlayerInformation desc =
                            c.GetAPlayer(c.GetPlayerID());
                        desc.vPos.x -= 10;
                        olc::net::message<CustomMsgTypes> msg;
                        msg.header.id =
                            CustomMsgTypes::Game_UpdatePositionEntity;
                        msg << desc;
                        std::cout << "Update Player [" << desc.nUniqueID
                                  << "] at (" << desc.vPos.x << ","
                                  << desc.vPos.y << ")" << std::endl;
                        c.Send(msg);
                    } break;
                    case sf::Keyboard::Right: {
                        sPlayerInformation desc =
                            c.GetAPlayer(c.GetPlayerID());
                        desc.vPos.x += 10;
                        olc::net::message<CustomMsgTypes> msg;
                        msg.header.id =
                            CustomMsgTypes::Game_UpdatePositionEntity;
                        msg << desc;
                        std::cout << "Update Player [" << desc.nUniqueID
                                  << "] at (" << desc.vPos.x << ","
                                  << desc.vPos.y << ")" << std::endl;
                        c.Send(msg);
                    } break;
                    default:
                        break;
                    }
                }
                if (event.type == sf::Event::Closed)
                    window.close();
                olc::net::message<CustomMsgTypes> msg;
                msg.header.id = CustomMsgTypes::Game_UpdateEntity;
                c.Send(msg);
                window.clear();
                for (auto &player : c.getPlayers()) {
                    carre.setPosition(
                        player.second.vPos.x, player.second.vPos.y);
                    carre.setFillColor(sf::Color::White);
                    window.draw(carre);
                    window.display();
                }
            } else {
                std::cout << "Not Connected" << std::endl;
            }
        }
    }
}
