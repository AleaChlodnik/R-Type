/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include "Entities/entity_factory.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>

Entity EntityFactory::createBackground(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity background = entityManager.createEntity();

    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(0.6f, 0.6f);

    BackgroundComponent backgroundComponent;
    PositionComponent start_position(0, 0);
    VelocityComponent velocity(200.0f);
    OffsetComponent offset(0);
    SpriteComponent sprite(texture, start_position, scale);

    componentManager.addComponent<BackgroundComponent>(background.getId(), backgroundComponent);
    componentManager.addComponent<PositionComponent>(background.getId(), start_position);
    componentManager.addComponent<VelocityComponent>(background.getId(), velocity);
    componentManager.addComponent<OffsetComponent>(background.getId(), offset);
    componentManager.addComponent<SpriteComponent>(background.getId(), sprite);

    return background;
}

Entity EntityFactory::createPlayer(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity player = entityManager.createEntity();

    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Player/Ship3/ship3.png");
    sf::Vector2f scale(1.3f, 1.3f);

    PlayerComponent playerComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity(100.0f);
    SpriteComponent sprite(texture, startPosition, scale);
    HitboxComponent hitbox{startPosition.x, startPosition.y, scale.x, scale.y};
    HealthComponent health(100, 100);
    InputComponent input(InputType::NONE);

    componentManager.addComponent<PlayerComponent>(player.getId(), playerComponent);
    componentManager.addComponent<PositionComponent>(player.getId(), startPosition);
    componentManager.addComponent<SpriteComponent>(player.getId(), sprite);
    componentManager.addComponent<HitboxComponent>(player.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(player.getId(), health);
    componentManager.addComponent<InputComponent>(player.getId(), input);

    return player;
}

Entity EntityFactory::createMissile(int playerId, EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity missle = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Missiles/missile.png");
    sf::Vector2f scale(0.1f, 0.1f);

    auto playerPosition = componentManager.getComponent<PositionComponent>(playerId);

    MissileComponent missileComponent;
    PositionComponent startPosition(
        playerPosition.value()->x + 105, playerPosition.value()->y + 49);
    VelocityComponent velocity(200.0f);
    SpriteComponent sprite(texture, startPosition, scale);
    HitboxComponent hitbox{startPosition.x, startPosition.y, scale.x, scale.y};

    componentManager.addComponent<MissileComponent>(missle.getId(), missileComponent);
    componentManager.addComponent<PositionComponent>(missle.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(missle.getId(), velocity);
    componentManager.addComponent<SpriteComponent>(missle.getId(), sprite);

    return missle;
}

Entity EntityFactory::createBasicMonster(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity monster = entityManager.createEntity();

    std::string texturePath;
    int monsterSprite = (std::rand() % 4) + 1;
    switch (monsterSprite) {
    case 1:
        texturePath = "Client/Assets/Sprites/Monsters/monster1.png";
        break;
    case 2:
        texturePath = "Client/Assets/Sprites/Monsters/monster2.png";
        break;
    case 3:
        texturePath = "Client/Assets/Sprites/Monsters/monster3.png";
        break;
    case 4:
        texturePath = "Client/Assets/Sprites/Monsters/monster4.png";
        break;
    default:
        break;
    }

    sf::Texture &texture = textureManager.getTexture(texturePath);
    sf::Vector2f scale(1.0f, 1.0f);

    BasicMonsterComponent monsterComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity(100.0f);
    SpriteComponent sprite(texture, startPosition, scale);
    HitboxComponent hitbox{startPosition.x, startPosition.y, scale.x, scale.y};

    return monster;
}
