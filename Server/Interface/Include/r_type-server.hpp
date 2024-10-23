// /*
// ** EPITECH PROJECT, 2024
// ** R-Type
// ** File description:
// ** r_type-server
// */

// #pragma once

// #include <errno.h>
// #include <signal.h>
// #include <stdio.h>
// #include "Net/server.hpp"

// namespace r_type {
// namespace server {

// class Handler {
//   public:
//     Handler();

//     static void signal_handler(int signal)
//     {
//         if (signal == SIGINT) {
//             instance->loopRunning = false;
//         }
//     }

//     void run(r_type::net::Server &server);

//     static r_type::server::Handler *instance;

//   private:
//     bool loopRunning;
// };
// }; // namespace game
// }; // namespace r_type