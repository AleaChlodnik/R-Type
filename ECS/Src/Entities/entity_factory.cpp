/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include "Components/components.hpp"
#include <Entities/entity_factory.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>

Entity EntityFactory::createBackground(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity background = entityManager.createEntity();

    BackgroundComponent backgroundComponent;
    PositionComponent start_position(0, 0);
    SpriteDataComponent spriteData{SpritePath::Background, {0, 0}, {6913, 3901}, {1.0f, 1.0f}};
    VelocityComponent velocity{200.0f};
    OffsetComponent offset{0};

    componentManager.addComponent<BackgroundComponent>(background.getId(), backgroundComponent);
    componentManager.addComponent<PositionComponent>(background.getId(), start_position);
    componentManager.addComponent<VelocityComponent>(background.getId(), velocity);
    componentManager.addComponent<OffsetComponent>(background.getId(), offset);
    componentManager.addComponent<SpriteDataComponent>(background.getId(), spriteData);

    return background;
}

Entity EntityFactory::createPlayer(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity player = entityManager.createEntity();

    PlayerComponent playerComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{100.0f};
    SpriteDataComponent spriteData{SpritePath::Ship1, {16, 40}, {96, 48}, {1.5f, 1.5f}};
    HitboxComponent hitbox{spriteData.dimension.x, spriteData.dimension.y};
    HealthComponent health{100, 100};
    InputComponent input{InputType::NONE};

    componentManager.addComponent<PlayerComponent>(player.getId(), playerComponent);
    componentManager.addComponent<PositionComponent>(player.getId(), startPosition);
    componentManager.addComponent<HitboxComponent>(player.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(player.getId(), health);
    componentManager.addComponent<InputComponent>(player.getId(), input);
    componentManager.addComponent<SpriteDataComponent>(player.getId(), spriteData);

    return player;
}

Entity EntityFactory::createAlly(EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity ally = entityManager.createEntity();

    AllyComponent allyComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{100.0f};
    SpriteDataComponent spriteData{SpritePath::Ship1, {16, 40}, {96, 48}, {1.0f, 1.0f}};
    HitboxComponent hitbox{spriteData.dimension.x, spriteData.dimension.y};
    HealthComponent health{100, 100};

    componentManager.addComponent<AllyComponent>(ally.getId(), allyComponent);
    componentManager.addComponent<PositionComponent>(ally.getId(), startPosition);
    componentManager.addComponent<HitboxComponent>(ally.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(ally.getId(), health);
    componentManager.addComponent<SpriteDataComponent>(ally.getId(), spriteData);

    return ally;
}

Entity EntityFactory::createBasicEnemy(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity enemy = entityManager.createEntity();

    EnemyComponent enemyComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{100.0f};
    SpriteDataComponent spriteData{SpritePath::Enemy1, {0, 0}, {80, 160}, {1.0f, 1.0f}};
    HitboxComponent hitbox{spriteData.dimension.x, spriteData.dimension.y};
    HealthComponent health{100, 100};

    componentManager.addComponent<EnemyComponent>(enemy.getId(), enemyComponent);
    componentManager.addComponent<PositionComponent>(enemy.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(enemy.getId(), velocity);
    componentManager.addComponent<HitboxComponent>(enemy.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(enemy.getId(), health);
    componentManager.addComponent<SpriteDataComponent>(enemy.getId(), spriteData);

    return enemy;
}

Entity EntityFactory::createBasicMonster(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity monster = entityManager.createEntity();

    BasicMonsterComponent monsterComponent;
    VelocityComponent velocity{100.0f};
    SpriteDataComponent spriteData{SpritePath::Monster1, {104, 136}, {272, 224}, {0.8f, 0.8f}};
    PositionComponent startPosition(1000, 500);
    HitboxComponent hitbox{spriteData.dimension.x, spriteData.dimension.y};
    HealthComponent health{100, 100};

    componentManager.addComponent<BasicMonsterComponent>(monster.getId(), monsterComponent);
    componentManager.addComponent<PositionComponent>(monster.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(monster.getId(), velocity);
    componentManager.addComponent<HitboxComponent>(monster.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(monster.getId(), health);
    componentManager.addComponent<SpriteDataComponent>(monster.getId(), spriteData);

    return monster;
}

Entity EntityFactory::createPlayerMissile(EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity playerMissile = entityManager.createEntity();

    PlayerMissileComponent playerMissileComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{200.0f};
    SpriteDataComponent spriteData{SpritePath::Missile, {0, 0}, {16, 16}, {0.1f, 0.1f}};
    HitboxComponent hitbox{spriteData.dimension.x, spriteData.dimension.y};

    componentManager.addComponent<PlayerMissileComponent>(
        playerMissile.getId(), playerMissileComponent);
    componentManager.addComponent<PositionComponent>(playerMissile.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(playerMissile.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(playerMissile.getId(), spriteData);

    return playerMissile;
}

Entity EntityFactory::createAllyMissile(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity allyMissile = entityManager.createEntity();

    AllyMissileComponent allyMissileComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{200.0f};
    SpriteDataComponent spriteData{SpritePath::Missile, {0, 0}, {16, 16}, {1.0f, 1.0f}};
    HitboxComponent hitbox{spriteData.dimension.x, spriteData.dimension.y};

    componentManager.addComponent<AllyMissileComponent>(allyMissile.getId(), allyMissileComponent);
    componentManager.addComponent<PositionComponent>(allyMissile.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(allyMissile.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(allyMissile.getId(), spriteData);

    return allyMissile;
}

Entity EntityFactory::createEnemyMissile(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity enemyMissile = entityManager.createEntity();

    EnemyMissileComponent enemyMissileComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{200.0f};
    SpriteDataComponent spriteData{SpritePath::Missile, {0, 0}, {16, 16}, {1.0f, 1.0f}};
    HitboxComponent hitbox{spriteData.dimension.x, spriteData.dimension.y};

    componentManager.addComponent<EnemyMissileComponent>(
        enemyMissile.getId(), enemyMissileComponent);
    componentManager.addComponent<PositionComponent>(enemyMissile.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(enemyMissile.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(enemyMissile.getId(), spriteData);

    return enemyMissile;
}

Entity EntityFactory::createButton(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager, std::string text,
    std::function<Scenes *(Scenes *)> *onClick)
{
    Entity button = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Menus/Table.png");
    sf::Vector2f dimension(1.0f, 1.0f);

    PositionComponent pos(0, 0);
    TextComponent textComponent(text);
    OnClickComponent onClickfunction(*onClick);
    SpriteComponent sprite(texture, pos.x, pos.y, dimension);

    componentManager.addComponent<PositionComponent>(button.getId(), pos);
    componentManager.addComponent<OnClickComponent>(button.getId(), onClickfunction);
    componentManager.addComponent<TextComponent>(button.getId(), textComponent);
    componentManager.addComponent<SpriteComponent>(button.getId(), sprite);

    return button;
}

Entity EntityFactory::createSmallButton(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager, std::string text,
    std::function<Scenes *(Scenes *, Scenes::Actions)> *onClick)
{
    Entity button = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Menus/small_button.png");
    sf::Vector2f scale(1.0f, 1.0f);

    PositionComponent pos(0, 0);
    TextComponent textComponent(text);
    BindComponent bindComponent(*onClick);
    SpriteComponent sprite(texture, pos.x, pos.y, scale);

    componentManager.addComponent<PositionComponent>(button.getId(), pos);
    componentManager.addComponent<BindComponent>(button.getId(), bindComponent);
    componentManager.addComponent<TextComponent>(button.getId(), textComponent);
    componentManager.addComponent<SpriteComponent>(button.getId(), sprite);

    return button;
}