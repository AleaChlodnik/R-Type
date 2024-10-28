/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** audio_system
*/

#include <Systems/audio_system.hpp>

void AudioSystem::playBackgroundMusic(const std::string &filePath)
{
    if (_backgroundMusic.getStatus() != sf::Music::Playing || _currentMusicFilePath != filePath) {
        if (!_backgroundMusic.openFromFile(filePath)) {
            throw failedToLoadSound();
        }
        _backgroundMusic.setVolume(50.0f);
        _backgroundMusic.setLoop(true);
        _backgroundMusic.play();
        _currentMusicFilePath = filePath;
    }
}

void AudioSystem::stopBackgroundMusic()
{
    _backgroundMusic.stop();
}

void AudioSystem::playSoundEffect(const std::string &filePath)
{
    auto &buffer = _audioManager->getSoundBuffer(filePath);
    _soundEffect.setBuffer(buffer);
    _soundEffect.setVolume(70.0f);
    _soundEffect.play();
}
