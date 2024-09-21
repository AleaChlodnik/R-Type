/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <SFML/Graphics.hpp>

#include "r_type.hpp"

void simpleClient();

int main()
{
    // auto window = sf::RenderWindow{{1920u, 1080u}, "CMake SFML Project"};
    // window.setFramerateLimit(144);

    // while (window.isOpen()) {
    //     for (auto event = sf::Event{}; window.pollEvent(event);) {
    //         if (event.type == sf::Event::Closed) {
    //             window.close();
    //         }
    //     }

    //     window.clear();
    //     window.display();
    // }

    simpleClient();

    //printf("Hello World\n");

    return 0;
}
