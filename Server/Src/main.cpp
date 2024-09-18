/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

#ifndef _WIN32
    #define _WIN32_WINNT 0x0A00
#endif
#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <iostream>

int main()
{
    asio::error_code ec;

    asio::io_context context;

    asio::ip::tcp::endpoint endpoint(
        asio::ip::make_address("0.0.0.0", ec), 80);

    asio::ip::tcp::socket socket(context);

    socket.connect(endpoint, ec);

    if (!ec) {
        std::cout << "Connected !" << std::endl;
    } else {
        std::cout << "Failed to connect to address :\n" << ec.message() << std::endl;
    }
    return 0;
}
