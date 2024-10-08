/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <r_type_net_server.hpp>
#include <iostream>

int main()
{
    R_TypeNetServer server(60000);
    server.Start();

    while (1) {
        server.Update(-1, true);
    }

    return 0;
}