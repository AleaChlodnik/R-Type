/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <Net/server.hpp>
#include <iostream>

#include <errno.h>
#include <signal.h>
#include <stdio.h>

static bool loopRunning = true;

void signal_handler(int signal)
{
    if (signal == SIGINT)
        loopRunning = false;
}

static bool isValidPort(const std::string &portStr)
{
    // Check if the port string is empty or too long
    if (portStr.empty() || portStr.length() > 5) {
        return false;
    }

    // Check if the string contains only digits
    for (char c : portStr) {
        if (!isdigit(c)) {
            return false;
        }
    }

    // Convert the string to an integer
    int port = std::stoi(portStr);

    // Check if the port is within the valid range (0-65535)
    return port >= 1024 && port <= 65535;
}

int main(int const argc, char const *const *const argv)
{
    if (argc != 2) {
        std::cerr << "Usage: ./server <port>" << std::endl;
        return ERROR_EPITECH;
    }
    if (!isValidPort(argv[1])) {
        std::cerr << "Invalid port number, 1023 < port < 65536" << std::endl;
        return ERROR_EPITECH;
    }

    r_type::net::Server server(std::stoi(argv[1]));
    server.Start();

    signal(SIGINT, signal_handler);

    while (loopRunning) {
        server.Update(-1, true);
    }

    return OK;
}