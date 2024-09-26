/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** simpleClient
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <olcNet.hpp>

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
        std::cout << "Ping sent" << std::endl;
    }

    void MessageAll()
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::MessageAll;
        Send(msg);
    }
};

void simpleClient()
{
    CustomClient c;
    c.Connect("127.0.0.1", 60000);
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    sf::Event event;
    while (window.isOpen()) {
        if (c.IsConnected()) {
            if (!c.Incoming().empty()) {
                auto msg = c.Incoming().popFront().msg;
                switch (msg.header.id) {
                case CustomMsgTypes::ServerAccept: {
                    // Server has responded to a ping request
                    std::cout << "Server Accepted Connection" << std::endl;
                } break;

                case CustomMsgTypes::ServerPing: {
                    // Server has responded to a ping request
                    std::chrono::system_clock::time_point timeNow =
                        std::chrono::system_clock::now();
                    std::chrono::system_clock::time_point timeThen;
                    msg >> timeThen;
                    std::cout
                        << "Ping: "
                        << std::chrono::duration<double>(timeNow - timeThen)
                               .count()
                        << std::endl;
                } break;

                case CustomMsgTypes::ServerMessage: {
                    // Server has responded to a ping request
                    uint32_t clientID;
                    msg >> clientID;
                    std::cout << "Hello from [" << clientID << "]"
                              << std::endl;
                } break;
                case CustomMsgTypes::ServerDeny: {

                } break;
                case CustomMsgTypes::MessageAll: {

                } break;
                }
            }
        } else {
            std::cout << "Server Down" << std::endl;
            break;
        }

        while (window.pollEvent(event)) {
            // Close window if the close button is pressed
            if (event.type == sf::Event::Closed)
                window.close();
            switch (event.key.code) {
            case sf::Keyboard::Space: {
                c.PingServer();
                std::cout << "space" << std::endl;
            } break;
            case sf::Keyboard::Q: {
                window.close();
                std::cout << "Q" << std::endl;
            } break;
            case sf::Keyboard::V: {
                c.MessageAll();
                std::cout << "V" << std::endl;
            } break;
            default:
                break;
            }
        }

        // Clear the window
        window.clear();

        // Display the window
        window.display();
    }
}
