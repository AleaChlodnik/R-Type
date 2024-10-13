/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include "Entities/entity_factory.hpp"
#include "Components/components.hpp"
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

    std::string texturePath;
    int allies = 0;
    const auto &entities = entityManager.getAllEntities();
    for (const auto &entity : entities) {
        if (componentManager.getComponent<AllyComponent>(entity.getId())) {
            allies += 1;
        }
    }
    switch (allies) {
    case 0:
        texturePath = "Client/Assets/Sprites/Ships/ship1.png";
        break;
    case 1:
        texturePath = "Client/Assets/Sprites/Ships/ship2.png";
        break;
    case 2:
        texturePath = "Client/Assets/Sprites/Ships/ship3.png";
        break;
    case 3:
        texturePath = "Client/Assets/Sprites/Ships/ship4.png";
        break;
    case 4:
        texturePath = "Client/Assets/Sprites/Ships/ship5.png";
        break;
    case 5:
        texturePath = "Client/Assets/Sprites/Ships/ship6.png";
        break;
    default:
        break;
    }

    sf::Texture &texture = textureManager.getTexture(texturePath);
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

Entity EntityFactory::createAlly(EntityManager &entityManager, ComponentManager &componentManager,
    TextureManager &textureManager)
{
    std::string texturePath;
    int ships = 0;
    const auto &entities = entityManager.getAllEntities();
    for (const auto &entity : entities) {
        if (componentManager.getComponent<AllyComponent>(entity.getId()) ||
            componentManager.getComponent<PlayerComponent>(entity.getId())) {
            ships += 1;
        }
    }
    switch (ships) {
    case 0:
        texturePath = "Client/Assets/Sprites/Ships/ship1.png";
        break;
    case 1:
        texturePath = "Client/Assets/Sprites/Ships/ship2.png";
        break;
    case 2:
        texturePath = "Client/Assets/Sprites/Ships/ship3.png";
        break;
    case 3:
        texturePath = "Client/Assets/Sprites/Ships/ship4.png";
        break;
    case 4:
        texturePath = "Client/Assets/Sprites/Ships/ship5.png";
        break;
    case 5:
        texturePath = "Client/Assets/Sprites/Ships/ship6.png";
        break;
    default:
        break;
    }

    Entity ally = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture(texturePath);
    sf::Vector2f scale(1.3f, 1.3f);

    AllyComponent allyComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity(100.0f);
    SpriteComponent sprite(texture, startPosition, scale);
    HitboxComponent hitbox{startPosition.x, startPosition.y, scale.x, scale.y};
    HealthComponent health(100, 100);

    componentManager.addComponent<AllyComponent>(ally.getId(), allyComponent);
    componentManager.addComponent<PositionComponent>(ally.getId(), startPosition);
    componentManager.addComponent<SpriteComponent>(ally.getId(), sprite);
    componentManager.addComponent<HitboxComponent>(ally.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(ally.getId(), health);

    return ally;
}

Entity EntityFactory::createBasicEnemy(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity enemy = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Enemies/enemy5.png");
    sf::Vector2f scale(0.5f, 0.5f);

    EnemyComponent enemyComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity(100.0f);
    SpriteComponent sprite(texture, startPosition, scale);
    HitboxComponent hitbox{startPosition.x, startPosition.y, scale.x, scale.y};
    HealthComponent health(100, 100);

    componentManager.addComponent<EnemyComponent>(enemy.getId(), enemyComponent);
    componentManager.addComponent<PositionComponent>(enemy.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(enemy.getId(), velocity);
    componentManager.addComponent<SpriteComponent>(enemy.getId(), sprite);
    componentManager.addComponent<HitboxComponent>(enemy.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(enemy.getId(), health);

    return enemy;
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
    sf::Vector2f scale(0.25f, 0.25f);

    BasicMonsterComponent monsterComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity(100.0f);
    SpriteComponent sprite(texture, startPosition, scale);
    HitboxComponent hitbox{startPosition.x, startPosition.y, scale.x, scale.y};
    HealthComponent health(100, 100);

    componentManager.addComponent<BasicMonsterComponent>(monster.getId(), monsterComponent);
    componentManager.addComponent<PositionComponent>(monster.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(monster.getId(), velocity);
    componentManager.addComponent<SpriteComponent>(monster.getId(), sprite);
    componentManager.addComponent<HitboxComponent>(monster.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(monster.getId(), health);

    return monster;
}

Entity EntityFactory::createPlayerMissile(int playerId, EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity playerMissle = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Missiles/missile.png");
    sf::Vector2f scale(0.1f, 0.1f);

    auto playerPosition = componentManager.getComponent<PositionComponent>(playerId);

    PlayerMissileComponent playerMissileComponent;
    PositionComponent startPosition(
        playerPosition.value()->x + 105, playerPosition.value()->y + 49);
    VelocityComponent velocity(200.0f);
    SpriteComponent sprite(texture, startPosition, scale);
    HitboxComponent hitbox{startPosition.x, startPosition.y, scale.x, scale.y};

    componentManager.addComponent<PlayerMissileComponent>(playerMissle.getId(), playerMissileComponent);
    componentManager.addComponent<PositionComponent>(playerMissle.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(playerMissle.getId(), velocity);
    componentManager.addComponent<SpriteComponent>(playerMissle.getId(), sprite);

    return playerMissle;
}

Entity EntityFactory::createAllyMissile(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity allyMissile = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Missiles/missile.png");
    sf::Vector2f scale(0.1f, 0.1f);

    AllyMissileComponent allyMissileComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity(200.0f);
    SpriteComponent sprite(texture, startPosition, scale);
    HitboxComponent hitbox{startPosition.x, startPosition.y, scale.x, scale.y};

    componentManager.addComponent<AllyMissileComponent>(allyMissile.getId(), allyMissileComponent);
    componentManager.addComponent<PositionComponent>(allyMissile.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(allyMissile.getId(), velocity);
    componentManager.addComponent<SpriteComponent>(allyMissile.getId(), sprite);

    return allyMissile;
}

Entity EntityFactory::createEnemyMissile(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity enemyMissile = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Missiles/missile.png");
    sf::Vector2f scale(0.1f, 0.1f);

    EnemyMissileComponent enemyMissileComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity(200.0f);
    SpriteComponent sprite(texture, startPosition, scale);
    HitboxComponent hitbox{startPosition.x, startPosition.y, scale.x, scale.y};

    componentManager.addComponent<EnemyMissileComponent>(enemyMissile.getId(), enemyMissileComponent);
    componentManager.addComponent<PositionComponent>(enemyMissile.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(enemyMissile.getId(), velocity);
    componentManager.addComponent<SpriteComponent>(enemyMissile.getId(), sprite);

    return enemyMissile;
}
