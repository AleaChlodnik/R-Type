/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include <Entities/entity_factory.hpp>
#include "Components/components.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <spriteData.hpp>


Entity EntityFactory::createBackground(EntityManager &entityManager,
    ComponentManager &componentManager)
{
    Entity background = entityManager.createEntity();

    BackgroundComponent backgroundComponent;
    PositionComponent start_position(0, 0);
    VelocityComponent velocity{200.0f};
    OffsetComponent offset{0};

    componentManager.addComponent<BackgroundComponent>(background.getId(), backgroundComponent);
    componentManager.addComponent<PositionComponent>(background.getId(), start_position);
    componentManager.addComponent<VelocityComponent>(background.getId(), velocity);
    componentManager.addComponent<OffsetComponent>(background.getId(), offset);

    return background;
}

Entity EntityFactory::createPlayer(EntityManager &entityManager,
    ComponentManager &componentManager)
{
    Entity player = entityManager.createEntity();

    PlayerComponent playerComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{100.0f};
    SpriteData_t sprite = SpriteFactory(SpriteType::Ship1);
    HitboxComponent hitbox{startPosition.x, startPosition.y, sprite.scale.x, sprite.scale.y};
    HealthComponent health{100, 100};
    InputComponent input{InputType::NONE};

    componentManager.addComponent<PlayerComponent>(player.getId(), playerComponent);
    componentManager.addComponent<PositionComponent>(player.getId(), startPosition);
    componentManager.addComponent<HitboxComponent>(player.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(player.getId(), health);
    componentManager.addComponent<InputComponent>(player.getId(), input);

    return player;
}

Entity EntityFactory::createAlly(EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity ally = entityManager.createEntity();

    AllyComponent allyComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{100.0f};
    SpriteData_t sprite = SpriteFactory(SpriteType::Ship1);
    HitboxComponent hitbox{startPosition.x, startPosition.y, sprite.scale.x, sprite.scale.y};
    HealthComponent health{100, 100};

    componentManager.addComponent<AllyComponent>(ally.getId(), allyComponent);
    componentManager.addComponent<PositionComponent>(ally.getId(), startPosition);
    componentManager.addComponent<HitboxComponent>(ally.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(ally.getId(), health);

    return ally;
}

Entity EntityFactory::createBasicEnemy(EntityManager &entityManager,
    ComponentManager &componentManager)
{
    Entity enemy = entityManager.createEntity();

    EnemyComponent enemyComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{100.0f};
    SpriteData_t sprite = SpriteFactory(SpriteType::Enemy1);
    HitboxComponent hitbox{startPosition.x, startPosition.y, sprite.scale.x, sprite.scale.y};
    HealthComponent health{100, 100};

    componentManager.addComponent<EnemyComponent>(enemy.getId(), enemyComponent);
    componentManager.addComponent<PositionComponent>(enemy.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(enemy.getId(), velocity);
    componentManager.addComponent<HitboxComponent>(enemy.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(enemy.getId(), health);

    return enemy;
}

Entity EntityFactory::createBasicMonster(EntityManager &entityManager,
    ComponentManager &componentManager)
{
    Entity monster = entityManager.createEntity();

    BasicMonsterComponent monsterComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{100.0f};
    SpriteData_t sprite = SpriteFactory(SpriteType::Enemy1);
    HitboxComponent hitbox{startPosition.x, startPosition.y, sprite.scale.x, sprite.scale.y};
    HealthComponent health{100, 100};

    componentManager.addComponent<BasicMonsterComponent>(monster.getId(), monsterComponent);
    componentManager.addComponent<PositionComponent>(monster.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(monster.getId(), velocity);
    componentManager.addComponent<HitboxComponent>(monster.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(monster.getId(), health);

    return monster;
}

Entity EntityFactory::createPlayerMissile(int playerId, EntityManager &entityManager,
    ComponentManager &componentManager)
{
    Entity playerMissle = entityManager.createEntity();

    auto playerPosition = componentManager.getComponent<PositionComponent>(playerId);

    PlayerMissileComponent playerMissileComponent;
    PositionComponent startPosition(
        playerPosition.value()->x + 105, playerPosition.value()->y + 49);
    VelocityComponent velocity{200.0f};
    SpriteData_t sprite = SpriteFactory(SpriteType::Enemy1);
    HitboxComponent hitbox{startPosition.x, startPosition.y, sprite.scale.x, sprite.scale.y};

    componentManager.addComponent<PlayerMissileComponent>(
        playerMissle.getId(), playerMissileComponent);
    componentManager.addComponent<PositionComponent>(playerMissle.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(playerMissle.getId(), velocity);

    return playerMissle;
}

Entity EntityFactory::createAllyMissile(EntityManager &entityManager,
    ComponentManager &componentManager)
{
    Entity allyMissile = entityManager.createEntity();

    AllyMissileComponent allyMissileComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{200.0f};
    SpriteData_t sprite = SpriteFactory(SpriteType::Enemy1);
    HitboxComponent hitbox{startPosition.x, startPosition.y, sprite.scale.x, sprite.scale.y};

    componentManager.addComponent<AllyMissileComponent>(allyMissile.getId(), allyMissileComponent);
    componentManager.addComponent<PositionComponent>(allyMissile.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(allyMissile.getId(), velocity);

    return allyMissile;
}

Entity EntityFactory::createEnemyMissile(EntityManager &entityManager,
    ComponentManager &componentManager)
{
    Entity enemyMissile = entityManager.createEntity();

    EnemyMissileComponent enemyMissileComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{200.0f};
    SpriteData_t sprite = SpriteFactory(SpriteType::Enemy1);
    HitboxComponent hitbox{startPosition.x, startPosition.y, sprite.scale.x, sprite.scale.y};

    componentManager.addComponent<EnemyMissileComponent>(
        enemyMissile.getId(), enemyMissileComponent);
    componentManager.addComponent<PositionComponent>(enemyMissile.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(enemyMissile.getId(), velocity);

    return enemyMissile;
}

Entity EntityFactory::createButton(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager, std::string text,
    std::function<Scenes *(Scenes *)> *onClick)
{
    Entity button = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Menus/Table.png");
    sf::Vector2f scale(1.0f, 1.0f);

    PositionComponent pos(0, 0);
    TextComponent textComponent(text);
    OnClickComponent onClickfunction(*onClick);
    SpriteComponent sprite(texture, pos.x, pos.y, scale);

    componentManager.addComponent<PositionComponent>(button.getId(), pos);
    componentManager.addComponent<OnClickComponent>(button.getId(), onClickfunction);
    componentManager.addComponent<TextComponent>(button.getId(), textComponent);
    componentManager.addComponent<SpriteComponent>(button.getId(), sprite);

    return button;
}