/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** audio_manager
*/

#pragma once

#include "error_handling.hpp"
#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <unordered_map>

class AudioManager {
public:
    sf::SoundBuffer &getSoundBuffer(const std::string &filePath) {
        // Check if sound buffer is already cached
        auto it = soundBuffers.find(filePath);
        if (it != soundBuffers.end()) {
            return *it->second;
        }

        // Load and cache the sound buffer
        auto buffer = std::make_shared<sf::SoundBuffer>();
        if (!buffer->loadFromFile(filePath)) {
            throw std::runtime_error("Failed to load sound from " + filePath);
        }
        soundBuffers[filePath] = buffer;
        return *buffer;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers;
};
