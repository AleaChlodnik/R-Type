/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** simpleClient
*/

#include <Net/client.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

void simpleClient()
{
    r_type::net::Client c;
    c.Connect("127.0.0.1", 60000);
    std::cout << "Socket: " << c.getConnection()->getSocket() << std::endl;
    std::cout << "Endpoint: " << c.getConnection()->getEndpoint() << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Preferences");
    sf::Event event;

    auto updatePlayerPosition = [&](const vf2d &delta) {
        EntityInformation desc = c.GetAPlayer(c.GetEntityID());
        r_type::net::Message<TypeMessage> msg;
        desc.vPos.x += delta.x;
        desc.vPos.y += delta.y;
        msg.header.id = TypeMessage::MoveEntityMessage;
        msg << desc;
        c.Send(msg);
    };

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                r_type::net::Message<TypeMessage> msg;
                msg.header.id = TypeMessage::DestroyEntityMessage;
                msg << c.GetEntityID();
                c.Send(msg);
                window.close();
            }
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
                case sf::Keyboard::Up: {
                    updatePlayerPosition(vf2d(0, -5));
                } break;
                case sf::Keyboard::Down: {
                    updatePlayerPosition(vf2d(0, 5));
                } break;
                case sf::Keyboard::Left: {
                    updatePlayerPosition(vf2d(-5, 0));
                } break;
                case sf::Keyboard::Right: {
                    updatePlayerPosition(vf2d(5, 0));
                } break;
                default:
                    break;
                }
            }
        }
        if (c.IsConnected()) {
            if (!c.Incoming().empty()) {
                auto msg = c.Incoming().pop_front().msg;
                switch (msg.header.id) {
                case TypeMessage::ServerAccept: {
                    std::cout << "Server Accepted Connection" << std::endl;
                    EntityInformation entity;
                    msg >> entity;
                    c.AddEntity(entity);
                    c.SetEntityID(entity.uniqueID);
                } break;
                case TypeMessage::ServerPing: {
                    std::chrono::system_clock::time_point timeNow =
                        std::chrono::system_clock::now();
                    std::chrono::system_clock::time_point timeThen;
                    msg >> timeThen;
                    std::cout << "Ping: "
                              << std::chrono::duration<double>(timeNow - timeThen).count()
                              << std::endl;
                } break;
                case TypeMessage::ServerMessage: {
                    uint32_t clientID;
                    msg >> clientID;
                    std::cout << "Hello from [" << clientID << "]" << std::endl;
                } break;
                case TypeMessage::ServerDeny: {
                } break;
                case TypeMessage::MessageAll: {
                } break;
                case TypeMessage::ClientConnect: {
                } break;
                case TypeMessage::CreateEntityMessage: {
                    EntityInformation entity;
                    msg >> entity;
                    c.AddEntity(entity);
                } break;
                case TypeMessage::CreateEntityResponse: {
                } break;
                case TypeMessage::DestroyEntityMessage: {
                    r_type::net::Message<TypeMessage> reponse;
                    uint32_t id;
                    msg >> id;
                    c.RemoveEntity(id);
                    reponse.header.id = TypeMessage::DestroyEntityResponse;
                    c.Send(reponse);
                } break;
                case TypeMessage::UpdateEntity: {
                    r_type::net::Message<TypeMessage> reponse;
                    reponse.header.id = TypeMessage::UpdateEntityResponse;
                    EntityInformation entity;
                    msg >> entity;
                    c.UpdateEntity(entity);
                } break;
                }
            }
        } else {
            std::cout << "Server Down" << std::endl;
            window.close();
            break;
        }

        window.clear();
        for (const auto &player : c.GetPlayers()) {
            sf::RectangleShape carre({player.second.hitbox.width, player.second.hitbox.height});
            carre.setPosition(player.second.vPos.x, player.second.vPos.y);
            carre.setFillColor(sf::Color::White);
            window.draw(carre);
        }
        window.display();
    }
}
