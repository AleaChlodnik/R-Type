/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** client
*/

#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <vector>

class Client {
  public:
    Client();
    ~Client();

  protected:
    int _port;
    int _sockedFd;
    std::string _hostName;
    std::string _buffer;
    std::queue<std::vector<std::string>> _queue;
};
