/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** a_scene
*/

#include <a_scenes.hpp>

AScenes::AScenes(std::string ip, int port) : IScenes(), _ip(ip), _port(port)
{
    this->_currentScene = AScenes::Scene::MAIN_MENU;
}

/**
 * @brief Set the Scene object
 *
 * @param scene
 */
void AScenes::setScene(AScenes::Scene scene)
{
    this->_previousScene = this->_currentScene;
    this->_currentScene = scene;
}

/**
 * @brief Get the Previous Scene object
 *
 * @return Scene
 */
AScenes::Scene AScenes::getPreviousScene() { return _previousScene; }

/**
 * @brief Set the Daltonism object
 *
 * @param mode The daltonism mode to set
 */
void AScenes::setDaltonism(DaltonismMode const mode) { _currentDaltonismMode = mode; }
/**
 * @brief Set the Game Mode object
 *
 * @param mode
 */
void AScenes::setGameMode(GameParameters const mode) { _currentGameMode = mode; }

void AScenes::setDisplayDaltonismChoice(bool const displayDaltonismChoice)
{
    _displayDaltonismChoice = displayDaltonismChoice;
}

bool AScenes::getDisplayDaltonismChoice() const { return this->_displayDaltonismChoice; }

void AScenes::setDisplayGameModeChoice(bool const displayGameModeChoice)
{
    _displayGameModeChoice = displayGameModeChoice;
}

bool AScenes::getDisplayGameModeChoice() const { return _displayGameModeChoice; }

void AScenes::setDisplayKeyBindsChoice(bool const displayKeyBindsChoice)
{
    _displayKeyBindsChoice = displayKeyBindsChoice;
}

bool AScenes::getDisplayKeyBindsChoice() const { return _displayKeyBindsChoice; }

void AScenes::setIp(std::string ip) { _ip = ip; }

void AScenes::setPort(int port) { _port = port; }

std::string AScenes::getIp() const { return _ip; }

int AScenes::getPort() const { return _port; }