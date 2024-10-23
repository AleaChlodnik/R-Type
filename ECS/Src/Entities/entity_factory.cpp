/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include "hitbox_tmp.hpp"
#include <Components/components.hpp>
#include <Entities/entity_factory.hpp>
#include <SFML/Graphics.hpp>
#include <cstdint>
#include <cstdlib>

Entity EntityFactory::createBackground(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity background = entityManager.createEntity();

    BackgroundComponent backgroundComponent;
    PositionComponent start_position(0, 0);
    SpriteDataComponent spriteData{
        SpritePath::Background, 1, {1.0f, 1.0f}, {{0, 0}, {6913, 3901}}, SpriteType::BACKGROUND};
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
    EntityManager &entityManager, ComponentManager &componentManager, int nbOfPlayers)
{
    Entity player = entityManager.createEntity();

    PlayerComponent playerComponent;
    PositionComponent startPosition(10, static_cast<float>(rand() % 80));
    // VelocityComponent velocity{100.0f};
    SpriteDataComponent spriteData{
        SpritePath::Ship1, 1, {1.0f, 1.0f}, {{99.6, 17.2}, {96, 48}}, SpriteType::PLAYER};
    HitboxComponent hitbox{
        static_cast<int>(spriteData.rects.size.x), static_cast<int>(spriteData.rects.size.y)};
    HealthComponent health{100, 100};
    InputComponent input{InputType::NONE};

    if (nbOfPlayers == 2) {
        spriteData.spritePath = SpritePath::Ship2;
        spriteData.rects.offSet = {99.6, spriteData.rects.offSet.y * 2};
    } else if (nbOfPlayers == 3) {
        spriteData.spritePath = SpritePath::Ship3;
        spriteData.rects.offSet = {99.6, spriteData.rects.offSet.y * 3};
    } else if (nbOfPlayers == 4) {
        spriteData.spritePath = SpritePath::Ship4;
        spriteData.rects.offSet = {99.6, spriteData.rects.offSet.y * 4};
    }

    componentManager.addComponent<PlayerComponent>(player.getId(), playerComponent);
    componentManager.addComponent<PositionComponent>(player.getId(), startPosition);
    componentManager.addComponent<HitboxComponent>(player.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(player.getId(), health);
    componentManager.addComponent<InputComponent>(player.getId(), input);
    componentManager.addComponent<SpriteDataComponent>(player.getId(), spriteData);

    while (CheckEntityPosition(player.getId(), componentManager, entityManager) != -1) {
        auto getPosition = componentManager.getComponent<PositionComponent>(player.getId());
        getPosition.value()->y = static_cast<float>(rand() % 80);
    }

    return player;
}

Entity EntityFactory::createAlly(EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity ally = entityManager.createEntity();

    AllyComponent allyComponent;
    PositionComponent startPosition(0, 0);
    // VelocityComponent velocity{100.0f};
    SpriteDataComponent spriteData{
        SpritePath::Ship1, 1, {1.0f, 1.0f}, {{16, 40}, {96, 48}}, SpriteType::ALLY};
    HitboxComponent hitbox{
        static_cast<int>(spriteData.rects.size.x), static_cast<int>(spriteData.rects.size.y)};
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
    SpriteDataComponent spriteData{
        SpritePath::Enemy1, 1, {1.0f, 1.0f}, {{0, 0}, {80, 160}}, SpriteType::ENEMY};
    HitboxComponent hitbox{
        static_cast<int>(spriteData.rects.size.x), static_cast<int>(spriteData.rects.size.y)};
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
    SpriteDataComponent spriteData{
        SpritePath::Monster1, 1, {0.5f, 0.5f}, {{0, 0}, {1, 1}}, SpriteType::ENEMY};
    PositionComponent startPosition(80, 60);
    HitboxComponent hitbox{
        static_cast<int>(spriteData.rects.size.x), static_cast<int>(spriteData.rects.size.y)};
    HealthComponent health{100, 100};

    componentManager.addComponent<BasicMonsterComponent>(monster.getId(), monsterComponent);
    componentManager.addComponent<PositionComponent>(monster.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(monster.getId(), velocity);
    componentManager.addComponent<HitboxComponent>(monster.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(monster.getId(), health);
    componentManager.addComponent<SpriteDataComponent>(monster.getId(), spriteData);

    while (CheckEntityPosition(monster.getId(), componentManager, entityManager) != -1) {
        auto monsterPos = componentManager.getComponent<PositionComponent>(monster.getId());
        if (monsterPos) {
            monsterPos.value()->x = static_cast<float>(rand() % 100);
            if (monsterPos.value()->x < 60) {
                monsterPos.value()->x = 60;
            }
            monsterPos.value()->y = static_cast<float>(rand() % 100);
        }
    }

    return monster;
}

Entity EntityFactory::createPlayerMissile(
    EntityManager &entityManager, ComponentManager &componentManager, uint32_t entityId)
{
    Entity playerMissile = entityManager.createEntity();

    PlayerMissileComponent playerMissileComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{200.0f};
    SpriteDataComponent spriteData{
        SpritePath::Missile, 1, {0.1f, 0.1f}, {{0, 0}, {16, 16}}, SpriteType::OTHER};
    // HitboxComponent hitbox{static_cast<int>(spriteData.dimension.x),
    // static_cast<int>(spriteData.dimension.y)};
    HitboxComponent hitbox{
        static_cast<int>(spriteData.rects.size.x), static_cast<int>(spriteData.rects.size.y)};

    auto entityPos = componentManager.getComponent<PositionComponent>(entityId);
    if (entityPos) {
        startPosition.x = entityPos.value()->x + 4;
        startPosition.y = entityPos.value()->y;
    }

    componentManager.addComponent<PlayerMissileComponent>(
        playerMissile.getId(), playerMissileComponent);
    componentManager.addComponent<PositionComponent>(playerMissile.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(playerMissile.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(playerMissile.getId(), spriteData);
    componentManager.addComponent<HitboxComponent>(playerMissile.getId(), hitbox);

    return playerMissile;
}

Entity EntityFactory::createAllyMissile(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity allyMissile = entityManager.createEntity();

    AllyMissileComponent allyMissileComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{200.0f};
    SpriteDataComponent spriteData{
        SpritePath::Missile, 1, {0.1f, 0.1f}, {{0, 0}, {16, 16}}, SpriteType::OTHER};
    // HitboxComponent hitbox{static_cast<int>(spriteData.dimension.x),
    // static_cast<int>(spriteData.dimension.y)};
    HitboxComponent hitbox{
        static_cast<int>(spriteData.rects.size.x), static_cast<int>(spriteData.rects.size.y)};

    componentManager.addComponent<AllyMissileComponent>(allyMissile.getId(), allyMissileComponent);
    componentManager.addComponent<PositionComponent>(allyMissile.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(allyMissile.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(allyMissile.getId(), spriteData);
    componentManager.addComponent<HitboxComponent>(allyMissile.getId(), hitbox);

    return allyMissile;
}

Entity EntityFactory::createEnemyMissile(
    EntityManager &entityManager, ComponentManager &componentManager, uint32_t entityId)
{
    Entity enemyMissile = entityManager.createEntity();

    EnemyMissileComponent enemyMissileComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{200.0f};
    SpriteDataComponent spriteData{
        SpritePath::Missile, 1, {0.1f, 0.1f}, {{0, 0}, {16, 16}}, SpriteType::ENEMY};
    // HitboxComponent hitbox{static_cast<int>(spriteData.dimension.x),
    // static_cast<int>(spriteData.dimension.y)};
    HitboxComponent hitbox{
        static_cast<int>(spriteData.rects.size.x), static_cast<int>(spriteData.rects.size.y)};

    auto entityPos = componentManager.getComponent<PositionComponent>(entityId);
    if (entityPos) {
        startPosition.x = entityPos.value()->x + 4;
        startPosition.y = entityPos.value()->y;
    }

    componentManager.addComponent<EnemyMissileComponent>(
        enemyMissile.getId(), enemyMissileComponent);
    componentManager.addComponent<PositionComponent>(enemyMissile.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(enemyMissile.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(enemyMissile.getId(), spriteData);
    componentManager.addComponent<HitboxComponent>(enemyMissile.getId(), hitbox);

    return enemyMissile;
}

Entity EntityFactory::createButton(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager, std::string text,
    std::function<IScenes *(AScenes *)> *onClick, float x, float y)
{
    Entity button = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Menus/Table.png");
    sf::Vector2f dimension(1.0f, 1.0f);

    PositionComponent pos(x, y);
    TextComponent textComponent(text);
    OnClickComponent onClickfunction(*onClick);
    SpriteComponent sprite(texture, pos.x, pos.y, dimension, SpriteType::OTHER);

    componentManager.addComponent<PositionComponent>(button.getId(), pos);
    componentManager.addComponent<OnClickComponent>(button.getId(), onClickfunction);
    componentManager.addComponent<TextComponent>(button.getId(), textComponent);
    componentManager.addComponent<SpriteComponent>(button.getId(), sprite);

    return button;
}

Entity EntityFactory::createSmallButton(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager, std::string text,
    std::function<IScenes *(AScenes *, AScenes::Actions)> *onClick, float x, float y)
{
    Entity button = entityManager.createEntity();

    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Menus/small_button.png");
    sf::Vector2f scale(1.0f, 1.0f);

    PositionComponent pos(x, y);
    TextComponent textComponent(text);
    BindComponent bindComponent(*onClick);
    SpriteComponent sprite(texture, pos.x, pos.y, scale, SpriteType::OTHER);

    componentManager.addComponent<PositionComponent>(button.getId(), pos);
    componentManager.addComponent<BindComponent>(button.getId(), bindComponent);
    componentManager.addComponent<TextComponent>(button.getId(), textComponent);
    componentManager.addComponent<SpriteComponent>(button.getId(), sprite);

    return button;
}