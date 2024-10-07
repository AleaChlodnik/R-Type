/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** simpleClient
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <net_client.hpp>

class CustomClient : public r_type::net::ClientInterface<NetR_TypeMessage> {
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

void simpleClient()
{
    CustomClient c;
    c.Connect("127.0.0.1", 60000);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Preferences");
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (c.IsConnected()) {
                if (!c.Incoming().empty()) {
                    auto msg = c.Incoming().pop_front().msg;
                    switch (msg.header.id) {
                    case NetR_TypeMessage::ServerAccept: {
                        std::cout << "Server Accepted Connection" << std::endl;
                    } break;

                    case NetR_TypeMessage::ServerPing: {
                        std::chrono::system_clock::time_point timeNow =
                            std::chrono::system_clock::now();
                        std::chrono::system_clock::time_point timeThen;
                        msg >> timeThen;
                        std::cout << "Ping: "
                                  << std::chrono::duration<double>(timeNow - timeThen).count()
                                  << std::endl;
                    } break;

                    case NetR_TypeMessage::ServerMessage: {
                        uint32_t clientID;
                        msg >> clientID;
                        std::cout << "Hello from [" << clientID << "]" << std::endl;
                    } break;
                    case NetR_TypeMessage::ServerDeny: {

                    } break;
                    case NetR_TypeMessage::MessageAll: {

                    } break;
                    case NetR_TypeMessage::ClientConnect: {
                    } break;
                    }
                }
            } else {
                std::cout << "Server Down" << std::endl;
                window.close();
                break;
            }

            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
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
                default:
                    break;
                }
            }
        }

        window.clear();
        window.display();
    }
}
