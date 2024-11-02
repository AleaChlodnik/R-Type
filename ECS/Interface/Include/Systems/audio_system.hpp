/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** audio_system
*/

#pragma once

#include <SFML/Audio.hpp>
#include <Systems/i_system.hpp>
#include <audio_manager.hpp>
#include <error_handling.hpp>
#include <memory>
#include <string>

/**
 * @class AudioSystem
 * @brief Manages audio playback within the application.
 *
 * The AudioSystem class provides functionalities for playing background music
 * and sound effects. It utilizes the AudioManager for managing audio resources
 * and the SFML library for audio playback.
 *
 * @details
 * This class is responsible for handling audio playback in the application. It
 * allows for playing background music and sound effects from specified file paths.
 * The class ensures proper management of audio resources through the use of
 * std::shared_ptr for the AudioManager instance.
 *
 * @note
 * The AudioSystem class relies on the SFML library for audio playback functionalities.
 * Ensure that the SFML library is properly included and linked in your project.
 *
 * @see AudioManager
 * @see sf::Music
 * @see sf::Sound
 */
class AudioSystem : public ISystem {
  public:
    /**
     * @brief Constructs an AudioSystem object.
     *
     * @param audioManager A shared pointer to an AudioManager instance.
     */
    AudioSystem(std::shared_ptr<AudioManager> audioManager) : _audioManager(audioManager) {}

    /**
     * @brief Plays background music from the specified file.
     *
     * This function loads and plays background music from the given file path.
     * It is typically used to provide ambient music for the application.
     *
     * @param filePath The path to the audio file to be played as background music.
     */
    void playBackgroundMusic(const std::string &filePath);

    /**
     * @brief Stops the background music that is currently playing.
     *
     * This function halts any background music that is being played by the audio system.
     * It can be used to stop the music when it is no longer needed or when transitioning
     * to a different scene or state in the application.
     */
    void stopBackgroundMusic();

    /**
     * @brief Plays a sound effect from the specified file.
     *
     * This function loads and plays a sound effect from the given file path.
     * It is useful for triggering sound effects in response to game events.
     *
     * @param filePath The path to the sound effect file to be played.
     */
    void playSoundEffect(const std::string &filePath);

  private:
    /**
     * @brief A shared pointer to the AudioManager instance.
     *
     * This member variable holds a shared pointer to an AudioManager object,
     * which is responsible for managing audio resources and playback within
     * the system. The use of std::shared_ptr ensures that the AudioManager
     * instance is properly managed and deallocated when no longer in use.
     */
    std::shared_ptr<AudioManager> _audioManager;
    /**
     * @brief A class that provides functionality for playing music.
     *
     * The sf::Music class allows for streaming audio from a file or memory.
     * It is particularly useful for playing large audio files, such as background music,
     * as it does not load the entire file into memory.
     */
    sf::Music _backgroundMusic;
    /**
     * @brief Stores the file path of the currently playing music.
     */
    std::string _currentMusicFilePath;
    /**
     * @brief Represents a sound effect that can be played in the audio system.
     *
     * This member variable is an instance of the sf::Sound class from the SFML library,
     * which is used to handle the playback of short sound effects. It provides functionalities
     * to play, pause, stop, and manipulate sound properties such as volume, pitch, and loop
     * status.
     */
    sf::Sound _soundEffect;
};
