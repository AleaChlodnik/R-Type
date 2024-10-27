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
#include <macros.hpp>

std::ostream &operator<<(std::ostream &os, const SpritePath &spritePath)
{
    switch (spritePath) {
    case SpritePath::Ship1:
        os << static_cast<std::string>("Ship1");
        break;
    case SpritePath::Ship2:
        os << static_cast<std::string>("Ship2");
        break;
    case SpritePath::Ship3:
        os << static_cast<std::string>("Ship3");
        break;
    case SpritePath::Ship4:
        os << static_cast<std::string>("Ship4");
        break;
    case SpritePath::Enemy1:
        os << static_cast<std::string>("Enemy1");
        break;
    case SpritePath::Enemy2:
        os << static_cast<std::string>("Enemy2");
        break;
    case SpritePath::Enemy3:
        os << static_cast<std::string>("Enemy3");
        break;
    case SpritePath::Enemy4:
        os << static_cast<std::string>("Enemy4");
        break;
    case SpritePath::Enemy5:
        os << static_cast<std::string>("Enemy5");
        break;
    case SpritePath::Enemy6:
        os << static_cast<std::string>("Enemy6");
        break;
    case SpritePath::Missile:
        os << static_cast<std::string>("Missile");
        break;
    case SpritePath::Background1:
        os << static_cast<std::string>("Background1");
        break;
    case SpritePath::Background2:
        os << static_cast<std::string>("Background2");
        break;
    case SpritePath::Background3:
        os << static_cast<std::string>("Background3");
        break;
    case SpritePath::Explosion:
        os << static_cast<std::string>("Explosion");
        break;
    case SpritePath::PowerUp:
        os << static_cast<std::string>("PowerUp");
        break;
    case SpritePath::Boss:
        os << static_cast<std::string>("Boss");
        break;
    case SpritePath::BossBullet:
        os << static_cast<std::string>("BossBullet");
        break;
    case SpritePath::NONE:
        os << static_cast<std::string>("NONE");
        break;
    default:
        os << static_cast<std::string>("Invalid SpritePath");
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const AScenes::SpriteType &spriteType)
{
    switch (spriteType) {
    case AScenes::SpriteType::BACKGROUND:
        os << static_cast<std::string>("BACKGROUND");
        break;
    case AScenes::SpriteType::PLAYER:
        os << static_cast<std::string>("PLAYER");
        break;
    case AScenes::SpriteType::ALLY:
        os << static_cast<std::string>("ALLY");
        break;
    case AScenes::SpriteType::ENEMY:
        os << static_cast<std::string>("ENEMY");
        break;
    case AScenes::SpriteType::OTHER:
        os << static_cast<std::string>("PLAOTHERYER");
        break;
    default:
        os << static_cast<std::string>("Invalid SpritePath");
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const SpriteDataComponent &spriteData)
{
    os << "SpriteDataComponent: " << std::endl;
    os << "spritePath: " << spriteData.spritePath << std::endl;
    os << "scale: " << spriteData.scale.x << ", " << spriteData.scale.y << std::endl;
    os << "rect: " << std::endl;
    os << "  offset: " << spriteData.rect.offset.x << ", " << spriteData.rect.offset.y
       << std::endl;
    os << "  dimension: " << spriteData.rect.dimension.x << ", " << spriteData.rect.dimension.y
       << std::endl;
    os << "type: " << spriteData.type << std::endl;
    return os;
}

Entity EntityFactory::createBackground(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity background = entityManager.createEntity();

    BackgroundComponent backgroundComponent;
    PositionComponent start_position(50, 50);
    // SpriteDataComponent spriteData{SpritePath::Background1, {5.625f, 5.625f}, {{0, 0}, {342,
    // 192}}, AScenes::SpriteType::BACKGROUND};
    SpriteDataComponent spriteData{SpritePath::Background1, {5.625f, 5.625f}, {{0, 0}, {342, 192}},
        AScenes::SpriteType::BACKGROUND};
    // OffsetComponent offset{0};

    componentManager.addComponent<BackgroundComponent>(background.getId(), backgroundComponent);
    componentManager.addComponent<PositionComponent>(background.getId(), start_position);
    // componentManager.addComponent<OffsetComponent>(background.getId(), offset);
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
        SpritePath::Ship1, {2.0f, 2.0f}, {{99.6, 0}, {33.2, 17.2}}, AScenes::SpriteType::PLAYER};
    switch (nbOfPlayers) {
    case 1: {
        spriteData.spritePath = SpritePath::Ship2;
        spriteData.rect.offset.y = 17.2;
    } break;
    case 2: {
        spriteData.spritePath = SpritePath::Ship3;
        spriteData.rect.offset.y = 17.2 * 2;
    } break;
    case 3: {
        spriteData.spritePath = SpritePath::Ship4;
        spriteData.rect.offset.y = 17.2 * 3;
    } break;
    default:
        break;
    }
    HitboxComponent hitbox{static_cast<int>(spriteData.rect.dimension.x),
        static_cast<int>(spriteData.rect.dimension.y)};
    HealthComponent health{100, 100};
    InputComponent input{InputType::NONE};

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

Entity EntityFactory::createBasicEnemy(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity monster = entityManager.createEntity();

    BasicMonsterComponent monsterComponent;
    VelocityComponent velocity{100.0f};
    // VelocityComponent velocity{1.0f}; ///////////////// temp
    SpriteDataComponent spriteData{
        SpritePath::Enemy1, {2.0f, 2.0f}, {{0, 0}, {37, 36}}, AScenes::SpriteType::ENEMY};
    PositionComponent startPosition(60, 60);
    HitboxComponent hitbox{static_cast<int>(spriteData.rect.dimension.x),
        static_cast<int>(spriteData.rect.dimension.y)};
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
        SpritePath::Missile, {1.0f, 1.0f}, {{249, 88}, {16, 8}}, AScenes::SpriteType::PLAYER};
    HitboxComponent hitbox{static_cast<int>(spriteData.rect.dimension.x),
        static_cast<int>(spriteData.rect.dimension.y)};

    auto entityPos = componentManager.getComponent<PositionComponent>(entityId);
    if (entityPos) {
        startPosition.x = entityPos.value()->x + 1;
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

Entity EntityFactory::createEnemyMissile(
    EntityManager &entityManager, ComponentManager &componentManager, uint32_t entityId)
{
    Entity enemyMissile = entityManager.createEntity();

    EnemyMissileComponent enemyMissileComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{200.0f};
    SpriteDataComponent spriteData{
        SpritePath::Missile, {0.1f, 0.1f}, {{0, 0}, {16, 16}}, AScenes::SpriteType::PLAYER};
    HitboxComponent hitbox{static_cast<int>(spriteData.rect.dimension.x),
        static_cast<int>(spriteData.rect.dimension.y)};

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
    SpriteComponent sprite(texture, pos.x, pos.y, dimension, AScenes::SpriteType::OTHER);

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
    SpriteComponent sprite(texture, pos.x, pos.y, scale, AScenes::SpriteType::OTHER);

    componentManager.addComponent<PositionComponent>(button.getId(), pos);
    componentManager.addComponent<BindComponent>(button.getId(), bindComponent);
    componentManager.addComponent<TextComponent>(button.getId(), textComponent);
    componentManager.addComponent<SpriteComponent>(button.getId(), sprite);

    return button;
}