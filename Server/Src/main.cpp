/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <iostream>
#include <Net/server.hpp>

int main()
{
    r_type::net::Server server(60000);
    server.Start();

    while (1) {
        server.Update(-1, true);
    }

    return 0;
}