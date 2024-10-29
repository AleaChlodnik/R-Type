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

class AudioSystem : public ISystem {
  public:
    AudioSystem(std::shared_ptr<AudioManager> audioManager) : _audioManager(audioManager) {}

    void playBackgroundMusic(const std::string &filePath);

    void stopBackgroundMusic();

    void playSoundEffect(const std::string &filePath);

  private:
    std::shared_ptr<AudioManager> _audioManager;
    sf::Music _backgroundMusic;
    std::string _currentMusicFilePath;
    sf::Sound _soundEffect;
};
