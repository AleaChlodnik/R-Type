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

/**
 * @class AudioManager
 * @brief Manages and caches sound buffers for efficient audio playback.
 *
 * The AudioManager class is responsible for loading, caching, and retrieving sound buffers.
 * It ensures that sound buffers are loaded only once and reused efficiently throughout the application.
 *
 * @note This class uses the SFML library for handling sound buffers.
 *
 * @fn sf::SoundBuffer& getSoundBuffer(const std::string &filePath)
 * @brief Retrieves a sound buffer from the specified file path.
 *
 * This function checks if the sound buffer is already cached. If it is, it returns the cached buffer.
 * Otherwise, it loads the sound buffer from the file, caches it, and then returns it.
 *
 * @param filePath The path to the sound file to be loaded.
 * @return A reference to the loaded sound buffer.
 * @throws std::runtime_error If the sound buffer fails to load from the specified file path.
 *
 * @var std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers
 * @brief A map that associates sound buffer names with their corresponding shared pointers to sf::SoundBuffer objects.
 *
 * This unordered map is used to store and manage sound buffers by their names, allowing for efficient retrieval and
 * usage of sound resources in the application. Each entry in the map consists of a string key representing the
 * name of the sound buffer and a shared pointer to an sf::SoundBuffer object, which ensures proper memory management
 * and resource sharing.
 */
class AudioManager {
  public:
    /**
     * @brief Retrieves a sound buffer from the specified file path.
     *
     * This function checks if the sound buffer is already cached. If it is,
     * the cached sound buffer is returned. Otherwise, it loads the sound buffer
     * from the file, caches it, and then returns it.
     *
     * @param filePath The path to the sound file.
     * @return A reference to the sound buffer.
     * @throws std::runtime_error If the sound buffer fails to load from the file.
     */
    sf::SoundBuffer &getSoundBuffer(const std::string &filePath)
    {
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
    /**
     * @brief A map that associates sound buffer names with their corresponding shared pointers to sf::SoundBuffer objects.
     *
     * This unordered map is used to store and manage sound buffers by their names, allowing for efficient retrieval and
     * usage of sound resources in the application. Each entry in the map consists of a string key representing the
     * name of the sound buffer and a shared pointer to an sf::SoundBuffer object, which ensures proper memory management
     * and resource sharing.
     */
    std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers;
};
