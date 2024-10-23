/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#include <iostream>
#include <macro.hpp>
#include <sstream>
#include <scenes.hpp>

static bool isValidIPv4(const std::string &ip)
{
    std::vector<std::string> parts;
    std::string part;
    std::stringstream ss(ip);

    // Split the IP string by '.'
    while (std::getline(ss, part, '.')) {
        parts.push_back(part);
    }

    // An IPv4 address must consist of 4 parts
    if (parts.size() != 4) {
        return false;
    }

    // Check each part to see if it's a valid number between 0 and 255
    for (const std::string &p : parts) {
        // Check if part is empty or larger than 3 characters
        if (p.empty() || p.length() > 3) {
            return false;
        }

        // Check if each character is a digit
        for (char c : p) {
            if (!isdigit(c)) {
                return false;
            }
        }

        // Convert the part to an integer
        int num = std::stoi(p);

        // Check if the number is between 0 and 255
        if (num < 0 || num > 255) {
            return false;
        }

        // Check if the part has leading zeros (e.g., "001" is invalid)
        if (p[0] == '0' && p.length() > 1) {
            return false;
        }
    }

    return true;
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

/**
 * @brief The entry point of the program.
 *
 * This function initializes the Rtype object and runs the game.
 *
 * @return 0 indicating successful program execution.
 *
 * @brief
 *
 * @return int
 */
int main(int const argc, char const *const *argv)
{

    if (argc != 3 || argv[1] == nullptr || argv[2] == nullptr) {
        std::cerr << "Usage: ./r-type_client <ip> <port>" << std::endl;
        return ERROR;
    }

    for (const char *p = argv[2]; *p != '\0'; ++p) {
        if (!std::isdigit(*p)) {
            std::cerr << "Port must be a number" << std::endl;
            return ERROR;
        }
    }
    if (!isValidIPv4(argv[1])) {
        std::cerr << "Invalid IP address" << std::endl;
        return ERROR;
    }

    if (!isValidPort(argv[2])) {
        std::cerr << "Invalid port number, 1023 < port < 65536" << std::endl;
        return ERROR;
    }

    std::unique_ptr<Scenes> scenes = std::make_unique<Scenes>(argv[1], atoi(argv[2]));
    scenes->run();
    return OK;
}
