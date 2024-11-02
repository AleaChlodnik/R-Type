/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** entity_factory
*/

#include <Systems/systems.hpp>
#include <animation_system.hpp>

// Define equality operator for vf2d
bool operator==(const vf2d &lhs, const vf2d &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }

/**
 * @brief Generates a vector representing the animation state of a ship.
 *
 * This function takes an AnimationShip enumeration value and returns a
 * vf2d vector that corresponds to the animation state of the ship.
 *
 * @param animation The animation state of the ship, represented by the
 * AnimationShip enumeration.
 *
 * @return vf2d A vector representing the animation state of the ship.
 * The x-coordinate of the vector corresponds to the frame position,
 * and the y-coordinate is always -1 for valid states. If the animation
 * state is not recognized, the function returns {0, 0}.
 */
vf2d animationShipFactory(AnimationShip animation)
{
    switch (animation) {
    case AnimationShip::SHIP_DOWN: {
        return {0, -1};
    } break;
    case AnimationShip::SHIP_FLIP_DOWN: {
        return {33.2, -1};
    } break;
    case AnimationShip::SHIP_STRAIT: {
        return {66.4, -1};
    } break;
    case AnimationShip::SHIP_FLIP_UP: {
        return {99.6, -1};
    } break;
    case AnimationShip::SHIP_UP: {
        return {132.8, -1};
    } break;
    }
    return {0, 0};
}

vf2d animationBasicMonsterFactory(AnimationBasicMonster animation)
{
    switch (animation) {
    case AnimationBasicMonster::BASIC_MONSTER_DEFAULT: {
        return {0, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_1: {
        return {32.8, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_2: {
        return {32.8 * 2, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_3: {
        return {32.8 * 3, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_4: {
        return {32.8 * 4, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_5: {
        return {32.8 * 5, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_6: {
        return {32.8 * 6, -1};
    } break;
    case AnimationBasicMonster::BASIC_MONSTER_7: {
        return {32.8 * 7, -1};
    } break;
    }
    return {0, 0};
}

static vf2d animationForceWeapon1Factory(AnimationForceWeapon1 animation)
{
    switch (animation) {
    case AnimationForceWeapon1::FORCE_WEAPON_DEFAULT: {
        return {300 + 0, 35};
    } break;
    case AnimationForceWeapon1::FORCE_WEAPON_1: {
        return {300 + 24, 35};
    } break;
    case AnimationForceWeapon1::FORCE_WEAPON_2: {
        return {300 + 24 * 2, 35};
    } break;
    case AnimationForceWeapon1::FORCE_WEAPON_3: {
        return {300 + 24 * 3, 35};
    } break;
    case AnimationForceWeapon1::FORCE_WEAPON_4: {
        return {300 + 24 * 4, 35};
    } break;
    case AnimationForceWeapon1::FORCE_WEAPON_5: {
        return {300 + 24 * 5, 35};
    } break;
    }
    return {0, 0};
}

static vf2d animationForceWeapon2Factory(AnimationForceWeapon2 animation)
{
    switch (animation) {
    case AnimationForceWeapon2::FORCE_WEAPON_DEFAULT: {
        return {120 + 0, 69};
    } break;
    case AnimationForceWeapon2::FORCE_WEAPON_1: {
        return {120 + 30, 69};
    } break;
    case AnimationForceWeapon2::FORCE_WEAPON_2: {
        return {120 + 30 * 2, 69};
    } break;
    case AnimationForceWeapon2::FORCE_WEAPON_3: {
        return {120 + 30 * 3, 69};
    } break;
    case AnimationForceWeapon2::FORCE_WEAPON_4: {
        return {120 + 30 * 4, 69};
    } break;
    case AnimationForceWeapon2::FORCE_WEAPON_5: {
        return {120 + 30 * 5, 69};
    } break;
    }
    return {0, 0};
}

static vf2d animationForceWeapon3Factory(AnimationForceWeapon3 animation)
{
    switch (animation) {
    case AnimationForceWeapon3::FORCE_WEAPON_DEFAULT: {
        return {173 + 0, 342};
    } break;
    case AnimationForceWeapon3::FORCE_WEAPON_1: {
        return {173 + 31.5, 342};
    } break;
    case AnimationForceWeapon3::FORCE_WEAPON_2: {
        return {173 + 31.5 * 2, 342};
    } break;
    case AnimationForceWeapon3::FORCE_WEAPON_3: {
        return {173 + 31.5 * 3, 342};
    } break;
    }
    return {0, 0};
}

static vf2d animationForceMissile1Factory(AnimationForceMissile1 animation)
{
    switch (animation) {
    case AnimationForceMissile1::FORCE_MISSILE_DEFAULT: {
        return {284, 59};
    } break;
    }
    return {0, 0};
}

static vf2d animationForceMissile2Factory(AnimationForceMissile2 animation)
{
    switch (animation) {
    case AnimationForceMissile2::FORCE_MISSILE_DEFAULT: {
        return {300, 224};
    } break;
    }
    return {0, 0};
}

static vf2d animationForceMissile3Factory(AnimationForceMissile3 animation)
{
    switch (animation) {
    case AnimationForceMissile3::FORCE_MISSILE_DEFAULT: {
        return {25 + 68.75 * 0, 470};
    } break;
    case AnimationForceMissile3::FORCE_MISSILE_1: {
        return {25 + 68.75 * 1, 470};
    } break;
    case AnimationForceMissile3::FORCE_MISSILE_2: {
        return {25 + 68.75 * 2, 470};
    } break;
    case AnimationForceMissile3::FORCE_MISSILE_3: {
        return {25 + 68.75 * 3, 470};
    } break;
    case AnimationForceMissile3::FORCE_MISSILE_4: {
        return {25 + 68.75 * 0, 470 + 34};
    } break;
    case AnimationForceMissile3::FORCE_MISSILE_5: {
        return {25 + 68.75 * 1, 470 + 34};
    } break;
    case AnimationForceMissile3::FORCE_MISSILE_6: {
        return {25 + 68.75 * 2, 470 + 34};
    } break;
    case AnimationForceMissile3::FORCE_MISSILE_7: {
        return {25 + 68.75 * 3, 470 + 34};
    } break;
    }
    return {0, 0};
}

/**
 * @brief Inequality operator for AnimationComponent.
 *
 * This operator compares two AnimationComponent objects to determine if they are not equal.
 * Two AnimationComponent objects are considered not equal if any of their respective
 * offset or dimension coordinates differ.
 *
 * @param animation The first AnimationComponent to compare.
 * @param other The second AnimationComponent to compare.
 * @return true if the AnimationComponent objects are not equal, false otherwise.
 */
bool operator!=(AnimationComponent animation, AnimationComponent other)
{
    return (animation.offset.x != other.offset.x || animation.offset.y != other.offset.y ||
        animation.dimension.x != other.dimension.x || animation.dimension.y != other.dimension.y);
}

/**
 * @brief Updates the animation states of entities based on their components.
 *
 * This function iterates through all entities and updates their animation
 * states based on the presence and values of specific components such as
 * AnimationComponent, PlayerComponent, VelocityComponent, and BackgroundComponent.
 *
 * @param componentManager Reference to the ComponentManager that handles components.
 * @param entityManager Reference to the EntityManager that handles entities.
 * @param deltaTime The time elapsed since the last update, used for time-based animations.
 */
void AnimationSystem::AnimationEntities(ComponentManager &componentManager,
    EntityManager &entityManager, float deltaTime, bool &endOfLevel)
{
    for (auto entity : entityManager.getAllEntities()) {

        auto animation = componentManager.getComponent<AnimationComponent>(entity.getId());
        if (animation) {
            // animate system for ship
            auto player = componentManager.getComponent<PlayerComponent>(entity.getId());
            auto velocity = componentManager.getComponent<VelocityComponent>(entity.getId());
            if (player && velocity) {
                animatePlayer(velocity, animation);
            }

            // animate system for basic monster
            auto basicMonster =
                componentManager.getComponent<BasicMonsterComponent>(entity.getId());
            if (basicMonster) {
                animateBasicMonster(animation);
            }

            // animate system for force weapon
            auto forceWeapon = componentManager.getComponent<ForceWeaponComponent>(entity.getId());
            if (forceWeapon) {
                animateForceWeapon(forceWeapon, animation);
            }
            // animate system for force missile
            auto forceMissile =
                componentManager.getComponent<ForceMissileComponent>(entity.getId());
            if (forceMissile) {
                auto forceWeaponOfForceMissile =
                    componentManager.getComponent<ForceWeaponComponent>(
                        forceMissile.value()->forceId);
                if (forceWeaponOfForceMissile) {
                    animateForceMissile(forceWeaponOfForceMissile, animation);
                }
            }

            // animate system for background
            if (auto background =
                    componentManager.getComponent<BackgroundComponent>(entity.getId())) {
                if (animation.value()->offset.x < 2700) {
                    animation.value()->offset.x += 1;
                    // animation.value()->offset.x += 5; //////////////////////// temp
                } else {
                    if (endOfLevel == false)
                        endOfLevel = true;
                }
            }
        }
    }
}

void AnimationSystem::animatePlayer(
    std::optional<VelocityComponent *> &velocity, std::optional<AnimationComponent *> &animation)
{
    if (velocity.value()->y >= -1 && velocity.value()->y < -0.6) {
        animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_DOWN).x;
    } else if (velocity.value()->y >= -0.6 && velocity.value()->y < -0.2) {
        animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_FLIP_DOWN).x;
    } else if (velocity.value()->y >= -0.2 && velocity.value()->y < 0.2) {
        animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_STRAIT).x;
    } else if (velocity.value()->y >= 0.2 && velocity.value()->y < 0.6) {
        animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_FLIP_UP).x;
    } else if (velocity.value()->y >= 0.6 && velocity.value()->y < 1) {
        animation.value()->offset.x = animationShipFactory(AnimationShip::SHIP_UP).x;
    }
    if (velocity.value()->y < 0) {
        velocity.value()->y += 0.05;
    } else if (velocity.value()->y > 0) {
        velocity.value()->y -= 0.05;
    }
}

void AnimationSystem::animateBasicMonster(std::optional<AnimationComponent *> &animation)
{
    if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_DEFAULT).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_1).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_1).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_2).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_2).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_3).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_3).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_4).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_4).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_5).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_5).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_6).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_6).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_7).x;
    } else if (animation.value()->offset.x ==
        animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_7).x) {
        animation.value()->offset.x =
            animationBasicMonsterFactory(AnimationBasicMonster::BASIC_MONSTER_DEFAULT).x;
    }
}

static void animateForceWeaponLevel1(std::optional<AnimationComponent *> &animation)
{
    if (animation.value()->offset.x ==
        animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_DEFAULT).x) {
        animation.value()->offset =
            animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_1);
    } else if (animation.value()->offset.x ==
        animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_1).x) {
        animation.value()->offset =
            animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_2);
    } else if (animation.value()->offset.x ==
        animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_2).x) {
        animation.value()->offset =
            animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_3);
    } else if (animation.value()->offset.x ==
        animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_3).x) {
        animation.value()->offset =
            animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_4);
    } else if (animation.value()->offset.x ==
        animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_4).x) {
        animation.value()->offset =
            animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_5);
    } else if (animation.value()->offset.x ==
        animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_5).x) {
        animation.value()->offset =
            animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_DEFAULT);
    } else {
        // default animation
        animation.value()->offset =
            animationForceWeapon1Factory(AnimationForceWeapon1::FORCE_WEAPON_DEFAULT);
    }
}

static void animateForceWeaponLevel2(std::optional<AnimationComponent *> &animation)
{
    if (animation.value()->offset.x ==
        animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_DEFAULT).x) {
        animation.value()->offset =
            animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_1);
    } else if (animation.value()->offset.x ==
        animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_1).x) {
        animation.value()->offset =
            animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_2);
    } else if (animation.value()->offset.x ==
        animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_2).x) {
        animation.value()->offset =
            animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_3);
    } else if (animation.value()->offset.x ==
        animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_3).x) {
        animation.value()->offset =
            animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_4);
    } else if (animation.value()->offset.x ==
        animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_4).x) {
        animation.value()->offset =
            animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_5);
    } else if (animation.value()->offset.x ==
        animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_5).x) {
        animation.value()->offset =
            animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_DEFAULT);
    } else {
        // default animation
        animation.value()->offset =
            animationForceWeapon2Factory(AnimationForceWeapon2::FORCE_WEAPON_DEFAULT);
    }
}

static void animateForceWeaponLevel3(std::optional<AnimationComponent *> &animation)
{
    if (animation.value()->offset.x ==
        animationForceWeapon3Factory(AnimationForceWeapon3::FORCE_WEAPON_DEFAULT).x) {
        animation.value()->offset =
            animationForceWeapon3Factory(AnimationForceWeapon3::FORCE_WEAPON_1);
    } else if (animation.value()->offset.x ==
        animationForceWeapon3Factory(AnimationForceWeapon3::FORCE_WEAPON_1).x) {
        animation.value()->offset =
            animationForceWeapon3Factory(AnimationForceWeapon3::FORCE_WEAPON_2);
    } else if (animation.value()->offset.x ==
        animationForceWeapon3Factory(AnimationForceWeapon3::FORCE_WEAPON_2).x) {
        animation.value()->offset =
            animationForceWeapon3Factory(AnimationForceWeapon3::FORCE_WEAPON_3);
    } else if (animation.value()->offset.x ==
        animationForceWeapon3Factory(AnimationForceWeapon3::FORCE_WEAPON_3).x) {
        animation.value()->offset =
            animationForceWeapon3Factory(AnimationForceWeapon3::FORCE_WEAPON_DEFAULT);
    } else {
        // default animation
        animation.value()->offset =
            animationForceWeapon3Factory(AnimationForceWeapon3::FORCE_WEAPON_DEFAULT);
    }
}

void AnimationSystem::animateForceWeapon(std::optional<ForceWeaponComponent *> &forceWeapon,
    std::optional<AnimationComponent *> &animation)
{
    switch (forceWeapon.value()->level) {
    case 1:
        animation.value()->dimension = {24, 16};
        animateForceWeaponLevel1(animation);
        break;
    case 2:
        animation.value()->dimension = {30, 24};
        animateForceWeaponLevel2(animation);
        break;
    case 3:
        animation.value()->dimension = {31.5, 33};
        animateForceWeaponLevel3(animation);
        break;
    default:
        animateForceWeaponLevel1(animation);
        break;
    }
}

static void animateForceMissileLevel1(std::optional<AnimationComponent *> &animation)
{
    // default animation
    animation.value()->offset =
        animationForceMissile1Factory(AnimationForceMissile1::FORCE_MISSILE_DEFAULT);
}

static void animateForceMissileLevel2(std::optional<AnimationComponent *> &animation)
{
    // default animation
    animation.value()->offset =
        animationForceMissile2Factory(AnimationForceMissile2::FORCE_MISSILE_DEFAULT);
}

static void animateForceMissileLevel3(std::optional<AnimationComponent *> &animation)
{
    if (animation.value()->offset ==
        animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_DEFAULT)) {
        animation.value()->offset =
            animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_1);
    } else if (animation.value()->offset ==
        animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_1)) {
        animation.value()->offset =
            animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_2);
    } else if (animation.value()->offset ==
        animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_2)) {
        animation.value()->offset =
            animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_3);
    } else if (animation.value()->offset ==
        animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_3)) {
        animation.value()->offset =
            animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_4);
    } else if (animation.value()->offset ==
        animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_4)) {
        animation.value()->offset =
            animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_5);
    } else if (animation.value()->offset ==
        animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_5)) {
        animation.value()->offset =
            animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_6);
    } else if (animation.value()->offset ==
        animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_6)) {
        animation.value()->offset =
            animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_7);
    } else if (animation.value()->offset ==
        animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_7)) {
        animation.value()->offset =
            animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_DEFAULT);
    } else {
        // default animation
        animation.value()->offset =
            animationForceMissile3Factory(AnimationForceMissile3::FORCE_MISSILE_DEFAULT);
    }
}

void AnimationSystem::animateForceMissile(std::optional<ForceWeaponComponent *> &forceWeapon,
    std::optional<AnimationComponent *> &animation)
{
    std::cout << "forceWeapon->level: " << forceWeapon.value()->level << std::endl;
    switch (forceWeapon.value()->level) {
    case 1:
        animation.value()->dimension = {16, 4};
        animateForceMissileLevel1(animation);
        break;
    case 2:
        animation.value()->dimension = {13, 3};
        animateForceMissileLevel2(animation);
        break;
    case 3:
        animation.value()->dimension = {68.75, 32};
        animateForceMissileLevel3(animation);
        break;
    default:
        animateForceMissileLevel1(animation);
        break;
    }
}