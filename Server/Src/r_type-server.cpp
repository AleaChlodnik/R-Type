// /*
// ** EPITECH PROJECT, 2024
// ** R-Type
// ** File description:
// ** r_type-server
// */

// #include <r_type-server.hpp>

// r_type::server::Handler::Handler() : loopRunning(true) {}

// void r_type::server::Handler::run(r_type::net::Server &server)
// {
//     signal(SIGINT, signal_handler);
//     while (loopRunning) {
//         server.Update(-1, true);
//     }
// }