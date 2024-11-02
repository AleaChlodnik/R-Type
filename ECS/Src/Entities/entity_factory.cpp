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
    // case SpritePath::Explosion:
    //     os << static_cast<std::string>("Explosion");
    //     break;
    // case SpritePath::PowerUp:
    //     os << static_cast<std::string>("PowerUp");
    //     break;
    case SpritePath::Boss:
        os << static_cast<std::string>("Boss");
        break;
    case SpritePath::BossBullet:
        os << static_cast<std::string>("BossBullet");
        break;
    case SpritePath::Bar:
        os << static_cast<std::string>("Bar");
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
        os << static_cast<std::string>("OTHER");
        break;
    default:
        os << static_cast<std::string>("Invalid SpritePath");
        break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const GameState &gameState)
{
    switch (gameState) {
    case GameState::LevelOne:
        os << static_cast<std::string>("LevelOne");
        break;
    case GameState::LevelTwo:
        os << static_cast<std::string>("LevelTwo");
        break;
    case GameState::LevelThree:
        os << static_cast<std::string>("LevelThree");
        break;
    case GameState::LevelFour:
        os << static_cast<std::string>("LevelFour");
        break;
    default:
        os << static_cast<std::string>("Invalid GameState");
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
    os << "type: " << spriteData.type << std::endl;
    return os;
}

Entity EntityFactory::backgroundFactory(
    EntityManager &entityManager, ComponentManager &componentManager, GameState type)
{
    std::cout << "Creating background" << std::endl;
    std::cout << "Type: " << type << std::endl;
    switch (type) {
    case GameState::LevelOne:
        return createBackgroundLevelOne(entityManager, componentManager);
        break;
    case GameState::LevelTwo:
        return createBackgroundLevelTwo(entityManager, componentManager);
        break;
    case GameState::LevelThree:
        return createBackgroundLevelThree(entityManager, componentManager);
        break;
    case GameState::LevelFour:
        return createBackgroundLevelFour(entityManager, componentManager);
        break;
    default:
        return createBackgroundLevelOne(entityManager, componentManager);
        break;
    }
}

Entity EntityFactory::createBackgroundLevelOne(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity background = entityManager.createEntity();

    BackgroundComponent backgroundComponent;
    PositionComponent start_position(50, 50);
    AnimationComponent animationComponent({0, 0}, {342, 192});
    SpriteDataComponent spriteData{
        SpritePath::Background1, {5.625f, 5.625f}, AScenes::SpriteType::BACKGROUND};

    componentManager.addComponent<BackgroundComponent>(background.getId(), backgroundComponent);
    componentManager.addComponent<PositionComponent>(background.getId(), start_position);
    componentManager.addComponent<SpriteDataComponent>(background.getId(), spriteData);
    componentManager.addComponent<AnimationComponent>(background.getId(), animationComponent);

    return background;
}

Entity EntityFactory::createBackgroundLevelTwo(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity background = entityManager.createEntity();

    BackgroundComponent backgroundComponent;
    PositionComponent start_position(50, 50);
    AnimationComponent animationComponent({0, 0}, {342, 192});
    SpriteDataComponent spriteData{
        SpritePath::Background1, {5.625f, 5.625f}, AScenes::SpriteType::BACKGROUND};

    componentManager.addComponent<BackgroundComponent>(background.getId(), backgroundComponent);
    componentManager.addComponent<PositionComponent>(background.getId(), start_position);
    componentManager.addComponent<SpriteDataComponent>(background.getId(), spriteData);
    componentManager.addComponent<AnimationComponent>(background.getId(), animationComponent);

    return background;
}

Entity EntityFactory::createBackgroundLevelThree(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity background = entityManager.createEntity();

    BackgroundComponent backgroundComponent;
    PositionComponent start_position(50, 50);
    AnimationComponent animationComponent({0, 0}, {342, 192});
    SpriteDataComponent spriteData{
        SpritePath::Background1, {5.625f, 5.625f}, AScenes::SpriteType::BACKGROUND};

    componentManager.addComponent<BackgroundComponent>(background.getId(), backgroundComponent);
    componentManager.addComponent<PositionComponent>(background.getId(), start_position);
    componentManager.addComponent<SpriteDataComponent>(background.getId(), spriteData);
    componentManager.addComponent<AnimationComponent>(background.getId(), animationComponent);

    return background;
}

Entity EntityFactory::createBackgroundLevelFour(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity background = entityManager.createEntity();

    BackgroundComponent backgroundComponent;
    PositionComponent start_position(50, 50);
    AnimationComponent animationComponent({0, 0}, {342, 192});
    SpriteDataComponent spriteData{
        SpritePath::Background1, {5.625f, 5.625f}, AScenes::SpriteType::BACKGROUND};

    componentManager.addComponent<BackgroundComponent>(background.getId(), backgroundComponent);
    componentManager.addComponent<PositionComponent>(background.getId(), start_position);
    componentManager.addComponent<SpriteDataComponent>(background.getId(), spriteData);
    componentManager.addComponent<AnimationComponent>(background.getId(), animationComponent);

    return background;
}

Entity EntityFactory::createBackgroundMenu(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager)
{
    Entity background = entityManager.createEntity();
    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Background/background.jpg");
    sf::Vector2f scale(1.0, 1.0);
    SpriteComponent spriteComponent(texture, 0, 0, scale, AScenes::SpriteType::BACKGROUND);
    componentManager.addComponent<SpriteComponent>(background.getId(), spriteComponent);
    return background;
}

Entity EntityFactory::createInfoBar(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity bar = entityManager.createEntity();
    Entity livesCategory = entityManager.createEntity();
    Entity scoreCategory = entityManager.createEntity();

    SpriteDataComponent spriteData{SpritePath::Bar, {0, 0}, AScenes::SpriteType::UI};
    TextDataComponent textData{FontPath::MAIN, static_cast<uint32_t>(60),
        {static_cast<uint32_t>(livesCategory.getId()),
            static_cast<uint32_t>(scoreCategory.getId())},
        {GameText::Lives, GameText::Score}, static_cast<uint32_t>(2)};

    componentManager.addComponent<SpriteDataComponent>(bar.getId(), spriteData);
    componentManager.addComponent<TextDataComponent>(bar.getId(), textData);

    return bar;
}

Entity EntityFactory::createPlayer(
    EntityManager &entityManager, ComponentManager &componentManager, int nbOfPlayers)
{
    Entity player = entityManager.createEntity();

    PlayerComponent playerComponent;
    FrontComponent frontComponent(-1);
    LinkForceComponent linkForceComponent(-1);
    PositionComponent startPosition(10, static_cast<float>(rand() % 80));
    VelocityComponent velocity{0.0f, 0.0f};
    ScoreComponent score{0};
    AnimationComponent animationComponent({99.6, 0}, {33.2, 17.2});
    SpriteDataComponent spriteData{SpritePath::Ship1, {2.0f, 2.0f}, AScenes::SpriteType::PLAYER};
    switch (nbOfPlayers) {
    case 1: {
        spriteData.spritePath = SpritePath::Ship2;
        animationComponent.offset.y = 17.2;
    } break;
    case 2: {
        spriteData.spritePath = SpritePath::Ship3;
        animationComponent.offset.y = 17.2 * 2;
    } break;
    case 3: {
        spriteData.spritePath = SpritePath::Ship4;
        animationComponent.offset.y = 17.2 * 3;
    } break;
    default:
        break;
    }
    HitboxComponent hitbox{static_cast<int>(animationComponent.dimension.x),
        static_cast<int>(animationComponent.dimension.y)};
    HealthComponent health{3};
    InputComponent input{InputType::NONE};

    componentManager.addComponent<PlayerComponent>(player.getId(), playerComponent);
    componentManager.addComponent<PositionComponent>(player.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(player.getId(), velocity);
    componentManager.addComponent<ScoreComponent>(player.getId(), score);
    componentManager.addComponent<AnimationComponent>(player.getId(), animationComponent);
    componentManager.addComponent<SpriteDataComponent>(player.getId(), spriteData);
    componentManager.addComponent<HitboxComponent>(player.getId(), hitbox);
    componentManager.addComponent<HealthComponent>(player.getId(), health);
    componentManager.addComponent<InputComponent>(player.getId(), input);
    componentManager.addComponent<FrontComponent>(player.getId(), frontComponent);
    componentManager.addComponent<LinkForceComponent>(player.getId(), linkForceComponent);

    return player;
}

Entity EntityFactory::createBasicMonster(
    EntityManager &entityManager, ComponentManager &componentManager, int posX, int posY)
{
    Entity monster = entityManager.createEntity();

    EnemyComponent enemyComponent;
    BasicMonsterComponent monsterComponent;
    VelocityComponent velocity{-1.0f, 0.0f};
    MovementComponent movement(MovementType::WIGGLE, 0, true);
    AnimationComponent animationComponent({0, 0}, {37, 36});
    SpriteDataComponent spriteData{SpritePath::Enemy1, {2.0f, 2.0f}, AScenes::SpriteType::ENEMY};
    PositionComponent startPosition(posX, posY);
    HitboxComponent hitbox{static_cast<int>(animationComponent.dimension.x),
        static_cast<int>(animationComponent.dimension.y)};

    componentManager.addComponent<EnemyComponent>(monster.getId(), enemyComponent);
    componentManager.addComponent<BasicMonsterComponent>(monster.getId(), monsterComponent);
    componentManager.addComponent<PositionComponent>(monster.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(monster.getId(), velocity);
    componentManager.addComponent<HitboxComponent>(monster.getId(), hitbox);
    componentManager.addComponent<SpriteDataComponent>(monster.getId(), spriteData);
    componentManager.addComponent<AnimationComponent>(monster.getId(), animationComponent);
    componentManager.addComponent<MovementComponent>(monster.getId(), movement);

    while (CheckEntityPosition(monster.getId(), componentManager, entityManager) != -1) {
        auto monsterPos = componentManager.getComponent<PositionComponent>(monster.getId());
        if (monsterPos) {
            monsterPos.value()->y = static_cast<float>(rand() % 100);
        }
    }

    return monster;
}

Entity EntityFactory::createShooterEnemy(
    EntityManager &entityManager, ComponentManager &componentManager, int posX, int posY)
{
    Entity enemy = entityManager.createEntity();

    EnemyComponent enemyComponent;
    VelocityComponent velocity{-1.0f, 0.0f};
    MovementComponent movement(MovementType::DIAGONAL, 0, true);
    AnimationComponent animationComponent({0, 0}, {37, 36});
    SpriteDataComponent spriteData{SpritePath::Enemy2, {2.0f, 2.0f}, AScenes::SpriteType::ENEMY};
    PositionComponent startPosition(posX, posY);
    HitboxComponent hitbox{static_cast<int>(animationComponent.dimension.x),
        static_cast<int>(animationComponent.dimension.y)};
    ShootComponent shoot{std::chrono::milliseconds(2000)};

    componentManager.addComponent<EnemyComponent>(enemy.getId(), enemyComponent);
    componentManager.addComponent<VelocityComponent>(enemy.getId(), velocity);
    componentManager.addComponent<AnimationComponent>(enemy.getId(), animationComponent);
    componentManager.addComponent<SpriteDataComponent>(enemy.getId(), spriteData);
    componentManager.addComponent<PositionComponent>(enemy.getId(), startPosition);
    componentManager.addComponent<HitboxComponent>(enemy.getId(), hitbox);
    componentManager.addComponent<ShootComponent>(enemy.getId(), shoot);
    componentManager.addComponent<MovementComponent>(enemy.getId(), movement);

    while (CheckEntityPosition(enemy.getId(), componentManager, entityManager) != -1) {
        auto enemyPos = componentManager.getComponent<PositionComponent>(enemy.getId());
        if (enemyPos) {
            enemyPos.value()->y = static_cast<float>(rand() % 100);
        }
    }

    return enemy;
}

Entity EntityFactory::createPlayerMissile(
    EntityManager &entityManager, ComponentManager &componentManager, uint32_t entityId)
{
    Entity playerMissile = entityManager.createEntity();

    // PlayerMissileComponent playerMissileComponent{static_cast<int>(entityId)};
    PlayerMissileComponent playerMissileComponent{entityId};
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{3.0f, 0.0f};
    MovementComponent movement;
    AnimationComponent animationComponent({249, 88}, {16, 8});
    SpriteDataComponent spriteData{SpritePath::Missile, {1.0f, 1.0f}, AScenes::SpriteType::PLAYER};
    HitboxComponent hitbox{static_cast<int>(animationComponent.dimension.x),
        static_cast<int>(animationComponent.dimension.y)};

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
    componentManager.addComponent<AnimationComponent>(playerMissile.getId(), animationComponent);
    componentManager.addComponent<MovementComponent>(playerMissile.getId(), movement);

    return playerMissile;
}

Entity EntityFactory::createForceWeapon(
    EntityManager &entityManager, ComponentManager &componentManager, uint32_t entityId)
{
    Entity forceWeapon = entityManager.createEntity();

    MovementComponent movement;
    ForceWeaponComponent weaponComponent(entityId, 1, false);
    PositionComponent startPosition(10, 50);
    VelocityComponent velocity{1.0f, 0.0f};
    AnimationComponent animationComponent({300, 35}, {24, 16});
    ShootComponent shootComponent(std::chrono::milliseconds(500));
    SpriteDataComponent spriteData{
        SpritePath::ForceWeapon, {2.0f, 2.0f}, AScenes::SpriteType::WEAPON};
    HitboxComponent hitbox{static_cast<int>(animationComponent.dimension.x),
        static_cast<int>(animationComponent.dimension.y)};

    componentManager.addComponent<ForceWeaponComponent>(forceWeapon.getId(), weaponComponent);
    componentManager.addComponent<PositionComponent>(forceWeapon.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(forceWeapon.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(forceWeapon.getId(), spriteData);
    componentManager.addComponent<HitboxComponent>(forceWeapon.getId(), hitbox);
    componentManager.addComponent<AnimationComponent>(forceWeapon.getId(), animationComponent);
    componentManager.addComponent<ShootComponent>(forceWeapon.getId(), shootComponent);
    componentManager.addComponent<MovementComponent>(forceWeapon.getId(), movement);

    return forceWeapon;
}

Entity EntityFactory::createForceMissile(
    EntityManager &entityManager, ComponentManager &componentManager, uint32_t forceId)
{
    Entity forceMissile = entityManager.createEntity();

    MovementComponent movement;
    ForceMissileComponent forceMissileComponent{forceId};
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{3.0f, 0.0f};
    AnimationComponent animationComponent({284, 59}, {16, 4});
    SpriteDataComponent spriteData{
        SpritePath::ForceMissile, {1.0f, 1.0f}, AScenes::SpriteType::WEAPON};
    HitboxComponent hitbox{static_cast<int>(animationComponent.dimension.x),
        static_cast<int>(animationComponent.dimension.y)};

    auto entityPos = componentManager.getComponent<PositionComponent>(forceId);
    if (entityPos) {
        startPosition.x = entityPos.value()->x + 1;
        startPosition.y = entityPos.value()->y;
    }

    componentManager.addComponent<ForceMissileComponent>(
        forceMissile.getId(), forceMissileComponent);
    componentManager.addComponent<PositionComponent>(forceMissile.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(forceMissile.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(forceMissile.getId(), spriteData);
    componentManager.addComponent<HitboxComponent>(forceMissile.getId(), hitbox);
    componentManager.addComponent<AnimationComponent>(forceMissile.getId(), animationComponent);
    componentManager.addComponent<MovementComponent>(forceMissile.getId(), movement);

    return forceMissile;
}

Entity EntityFactory::createPowerUpBlueLaserCrystal(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity powerUpBlueLaserCrystal = entityManager.createEntity();

    MovementComponent movement;
    PowerUpComponent powerUpComponent;
    PositionComponent startPosition(50, 50);
    VelocityComponent velocity{-0.2f, 0.0f};
    AnimationComponent animationComponent({0, 0}, {40, 36});
    SpriteDataComponent spriteData{
        SpritePath::BlueLaserCrystal, {1.0f, 1.0f}, AScenes::SpriteType::POWER_UP};
    HitboxComponent hitbox{static_cast<int>(animationComponent.dimension.x),
        static_cast<int>(animationComponent.dimension.y)};

    componentManager.addComponent<PowerUpComponent>(
        powerUpBlueLaserCrystal.getId(), powerUpComponent);
    componentManager.addComponent<PositionComponent>(
        powerUpBlueLaserCrystal.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(powerUpBlueLaserCrystal.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(
        powerUpBlueLaserCrystal.getId(), spriteData);
    componentManager.addComponent<HitboxComponent>(powerUpBlueLaserCrystal.getId(), hitbox);
    componentManager.addComponent<MovementComponent>(powerUpBlueLaserCrystal.getId(), movement);
    componentManager.addComponent<AnimationComponent>(
        powerUpBlueLaserCrystal.getId(), animationComponent);

    while (CheckEntityPosition(powerUpBlueLaserCrystal.getId(), componentManager, entityManager) !=
        -1) {
        auto powerUpBlueLaserCrystalPos =
            componentManager.getComponent<PositionComponent>(powerUpBlueLaserCrystal.getId());
        if (powerUpBlueLaserCrystalPos) {
            powerUpBlueLaserCrystalPos.value()->y = static_cast<float>(rand() % 100);
        }
    }

    return powerUpBlueLaserCrystal;
}

Entity EntityFactory::createEnemyMissile(
    EntityManager &entityManager, ComponentManager &componentManager, uint32_t entityId)
{
    Entity enemyMissile = entityManager.createEntity();

    EnemyMissileComponent enemyMissileComponent;
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{-3.0f, 0.0f};
    MovementComponent movement;
    AnimationComponent animationComponent({266, 88}, {16, 8});
    SpriteDataComponent spriteData{SpritePath::Missile, {1.0f, 1.0f}, AScenes::SpriteType::ENEMY};
    HitboxComponent hitbox{static_cast<int>(animationComponent.dimension.x),
        static_cast<int>(animationComponent.dimension.y)};

    auto entityPos = componentManager.getComponent<PositionComponent>(entityId);
    if (entityPos) {
        startPosition.x = entityPos.value()->x - 1;
        startPosition.y = entityPos.value()->y;
    }

    componentManager.addComponent<EnemyMissileComponent>(
        enemyMissile.getId(), enemyMissileComponent);
    componentManager.addComponent<PositionComponent>(enemyMissile.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(enemyMissile.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(enemyMissile.getId(), spriteData);
    componentManager.addComponent<HitboxComponent>(enemyMissile.getId(), hitbox);
    componentManager.addComponent<AnimationComponent>(enemyMissile.getId(), animationComponent);
    componentManager.addComponent<MovementComponent>(enemyMissile.getId(), movement);

    return enemyMissile;
}

Entity EntityFactory::createWall(
    EntityManager &entityManager, ComponentManager &componentManager, int posX, int posY)
{
    Entity wall = entityManager.createEntity();

    EnemyComponent enemyComponent;
    WallComponent wallComponent;
    MovementComponent movement;
    PositionComponent startPosition(posX, posY);
    VelocityComponent velocity{-1.0f, 0.0f};
    AnimationComponent animationComponent({0, 0}, {32, 32});
    SpriteDataComponent spriteData{SpritePath::Wall, {1.0f, 1.0f}, AScenes::SpriteType::ENEMY};
    HitboxComponent hitbox{static_cast<int>(animationComponent.dimension.x),
        static_cast<int>(animationComponent.dimension.y)};

    componentManager.addComponent<EnemyComponent>(wall.getId(), enemyComponent);
    componentManager.addComponent<WallComponent>(wall.getId(), wallComponent);
    componentManager.addComponent<PositionComponent>(wall.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(wall.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(wall.getId(), spriteData);
    componentManager.addComponent<HitboxComponent>(wall.getId(), hitbox);
    componentManager.addComponent<MovementComponent>(wall.getId(), movement);
    componentManager.addComponent<AnimationComponent>(wall.getId(), animationComponent);

    // while (CheckEntityPosition(wall.getId(), componentManager, entityManager) != -1) {
    //     auto wallPos = componentManager.getComponent<PositionComponent>(wall.getId());
    //     if (wallPos) {
    //         wallPos.value()->y = static_cast<float>(rand() % 100);
    //     }
    // }

    return wall;
}

Entity EntityFactory::createButton(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager, FontManager &fontManager,
    std::string text, std::function<IScenes *(AScenes *)> *onClick, float x, float y)
{
    Entity button = entityManager.createEntity();

    sf::Texture &texture = textureManager.getTexture("Client/Assets/Sprites/Menus/Table.png");
    sf::Font &font = fontManager.getFont(FontFactory(FontPath::MAIN));
    sf::Vector2f dimension(1.0f, 1.0f);

    PositionComponent pos(x, y);
    TextComponent textComponent(font, text, pos.x, pos.y);
    OnClickComponent onClickfunction(*onClick);
    SpriteComponent sprite(texture, pos.x, pos.y, dimension, AScenes::SpriteType::OTHER);

    componentManager.addComponent<PositionComponent>(button.getId(), pos);
    componentManager.addComponent<OnClickComponent>(button.getId(), onClickfunction);
    componentManager.addComponent<TextComponent>(button.getId(), textComponent);
    componentManager.addComponent<SpriteComponent>(button.getId(), sprite);

    return button;
}

Entity EntityFactory::createSmallButton(EntityManager &entityManager,
    ComponentManager &componentManager, TextureManager &textureManager, FontManager &fontManager,
    std::string text, std::function<IScenes *(AScenes *, AScenes::Actions)> *onClick, float x,
    float y)
{
    Entity button = entityManager.createEntity();

    sf::Texture &texture =
        textureManager.getTexture("Client/Assets/Sprites/Menus/small_button.png");
    sf::Font &font = fontManager.getFont(FontFactory(FontPath::MAIN));
    sf::Vector2f scale(1.0f, 1.0f);

    PositionComponent pos(x, y);
    TextComponent textComponent(font, text, pos.x, pos.y);
    BindComponent bindComponent(*onClick);
    SpriteComponent sprite(texture, pos.x, pos.y, scale, AScenes::SpriteType::OTHER);

    componentManager.addComponent<PositionComponent>(button.getId(), pos);
    componentManager.addComponent<BindComponent>(button.getId(), bindComponent);
    componentManager.addComponent<TextComponent>(button.getId(), textComponent);
    componentManager.addComponent<SpriteComponent>(button.getId(), sprite);

    return button;
}

Entity EntityFactory::createFilter(
    EntityManager &entityManager, ComponentManager &componentManager, AScenes::DaltonismMode mode)
{
    Entity filter = entityManager.createEntity();

    sf::Color filterColor;

    switch (mode) {
    case AScenes::DaltonismMode::PROTANOPIA:
        filterColor = sf::Color(255, 153, 102, 100);
        break;
    case AScenes::DaltonismMode::DEUTERANOPIA:
        filterColor = sf::Color(102, 153, 255, 100);
        break;
    case AScenes::DaltonismMode::TRITANOPIA:
        filterColor = sf::Color(255, 204, 255, 100);
        break;
    default:
        filterColor = sf::Color(255, 255, 255, 0);
        break;
    }

    sf::RectangleShape rectangle(sf::Vector2f(1920, 1080));
    rectangle.setFillColor(filterColor);

    RectangleShapeComponent rectangleShapeComponent(rectangle);

    componentManager.addComponent<PositionComponent>(filter.getId(), PositionComponent(0, 0));
    componentManager.addComponent<RectangleShapeComponent>(
        filter.getId(), rectangleShapeComponent);

    return filter;
}

Entity EntityFactory::createBoss(
    EntityManager &entityManager, ComponentManager &componentManager, EntityFactory &entityFactory)
{
    int tailLength = 5;
    std::vector<int> tailIds;
    Entity boss = entityManager.createEntity();

    for (int i = 0; i < (tailLength - 1); i++) {
        Entity tailSegment = entityFactory.createTailSegment(entityManager, componentManager);
        tailIds.push_back(tailSegment.getId());
    }
    Entity tailEnd = entityFactory.createTailEnd(entityManager, componentManager);
    tailIds.push_back(tailEnd.getId());

    BossComponent bossComponent{tailIds};
    PositionComponent position(90, 60);
    AnimationComponent animationComponent({24, 0}, {161.25, 208});
    SpriteDataComponent spriteData{SpritePath::Boss, {6.0f, 6.0f}, AScenes::SpriteType::ENEMY};
    HealthComponent health{10};
    HitboxComponent hitbox{static_cast<int>(animationComponent.dimension.x),
        static_cast<int>(animationComponent.dimension.y)};

    componentManager.addComponent<BossComponent>(boss.getId(), bossComponent);
    componentManager.addComponent<PositionComponent>(boss.getId(), position);
    componentManager.addComponent<AnimationComponent>(boss.getId(), animationComponent);
    componentManager.addComponent<SpriteDataComponent>(boss.getId(), spriteData);
    componentManager.addComponent<HealthComponent>(boss.getId(), health);
    componentManager.addComponent<HitboxComponent>(boss.getId(), hitbox);

    return boss;
}

Entity EntityFactory::createTailSegment(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity tailSegment = entityManager.createEntity();

    TailComponent tailComponent{};
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{0.0f, 0.0f};
    AnimationComponent animationComponent({544, 2000}, {16, 15});
    SpriteDataComponent spriteData{SpritePath::Boss, {1.0f, 1.0f}, AScenes::SpriteType::ENEMY};
    HitboxComponent hitbox{static_cast<int>(animationComponent.dimension.x),
        static_cast<int>(animationComponent.dimension.y)};

    componentManager.addComponent<TailComponent>(tailSegment.getId(), tailComponent);
    componentManager.addComponent<PositionComponent>(tailSegment.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(tailSegment.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(tailSegment.getId(), spriteData);
    componentManager.addComponent<HitboxComponent>(tailSegment.getId(), hitbox);
    componentManager.addComponent<AnimationComponent>(tailSegment.getId(), animationComponent);

    return tailSegment;
}

Entity EntityFactory::createTailEnd(
    EntityManager &entityManager, ComponentManager &componentManager)
{
    Entity tailEnd = entityManager.createEntity();

    TailComponent tailComponent{};
    PositionComponent startPosition(0, 0);
    VelocityComponent velocity{0.0f, 0.0f};
    AnimationComponent animationComponent({508, 2045}, {16, 16});
    SpriteDataComponent spriteData{SpritePath::Boss, {1.0f, 1.0f}, AScenes::SpriteType::ENEMY};
    HitboxComponent hitbox{static_cast<int>(animationComponent.dimension.x),
        static_cast<int>(animationComponent.dimension.y)};
    ShootComponent shoot{std::chrono::milliseconds(10000)};

    componentManager.addComponent<TailComponent>(tailEnd.getId(), tailComponent);
    componentManager.addComponent<PositionComponent>(tailEnd.getId(), startPosition);
    componentManager.addComponent<VelocityComponent>(tailEnd.getId(), velocity);
    componentManager.addComponent<SpriteDataComponent>(tailEnd.getId(), spriteData);
    componentManager.addComponent<HitboxComponent>(tailEnd.getId(), hitbox);
    componentManager.addComponent<AnimationComponent>(tailEnd.getId(), animationComponent);
    componentManager.addComponent<ShootComponent>(tailEnd.getId(), shoot);

    return tailEnd;
}
