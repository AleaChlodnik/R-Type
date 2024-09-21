/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** main
*/

// #ifndef _WIN32
// #define _WIN32_WINNT 0x0A00
// #endif
#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <chrono>
#include <iostream>

std::vector<char> vBuffer(20 * 1024);

void grabSomeData(asio::ip::tcp::socket &socket)
{
    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t lenght) {
            if (!ec) {
                std::cout << "\n\nRead" << lenght << " bytes\n\n";
                for (int i = 0; i < lenght; i++) {
                    std::cout << vBuffer[i];
                }
                grabSomeData(socket);
            }
        });
}

int main()
{
    asio::error_code ec;

    asio::io_context context;

    asio::io_context::work idleWork(context);

    std::thread thrContext = std::thread([&]() { context.run(); });

    asio::ip::tcp::endpoint endpoint(
        asio::ip::make_address("51.38.81.49", ec), 80);

    asio::ip::tcp::socket socket(context);

    socket.connect(endpoint, ec);

    if (!ec) {
        std::cout << "Connected !" << std::endl;
    } else {
        std::cout << "Failed to connect to address :\n"
                  << ec.message() << std::endl;
    }

    if (socket.is_open()) {
        grabSomeData(socket);

        std::string request = "GET /index.html HTTP/1.1\r\n"
                              "Host: example.com\r\n"
                              "Connection: close\r\n\r\n";

        socket.write_some(asio::buffer(request.data(), request.size()), ec);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(20000ms);

        context.stop();
        if (thrContext.joinable())
            thrContext.join();

    } else {
        std::cout << "Socket is not open !" << std::endl;
    }
    return 0;
}
