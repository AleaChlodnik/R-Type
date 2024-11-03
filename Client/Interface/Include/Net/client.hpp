/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** simpleClient
*/

#pragma once

#include <Net/a_client.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

namespace r_type {
namespace net {
class Client : virtual public r_type::net::AClient<TypeMessage> {
  public:
    /**
     * @brief Send a message to the server to get the ping
     *
     */
    void PingServer()
    {
        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::ServerPing;

        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

        msg << timeNow;
        Send(msg);
    }

    /**
     * @brief Send a message to the server to all other clients
     *
     */
    void MessageAll()
    {
        r_type::net::Message<TypeMessage> msg;
        msg.header.id = TypeMessage::MessageAll;
        Send(msg);
    }

    sf::Vector2u initInfoBar(UIEntityInformation entity, ComponentManager &componentManager,
        TextureManager &textureManager, FontManager &fontManager, sf::Vector2u windowSize)
    {
        float windowWidth = static_cast<float>(windowSize.x);
        float windowHeight = static_cast<float>(windowSize.y);

        sf::Texture &texture =
            textureManager.getTexture(SpriteFactory(entity.spriteData.spritePath));
        float desiredWidth = windowWidth;
        float desiredHeight = windowHeight * 0.10f;
        sf::Vector2f scale(
            desiredWidth / texture.getSize().x, desiredHeight / texture.getSize().y);
        SpriteComponent spriteComponent(texture, 0, 0, scale, entity.spriteData.type);
        componentManager.addComponent<SpriteComponent>(entity.uniqueID, spriteComponent);

        if (auto spriteEntity = componentManager.getComponent<SpriteComponent>(entity.uniqueID)) {
            spriteEntity.value()->sprite.setPosition(windowWidth / 2, windowHeight * 0.95f);
            sf::Font &font = fontManager.getFont(FontFactory(entity.textData.fontPath));

            sf::FloatRect spriteBounds = spriteEntity.value()->sprite.getLocalBounds();
            float barWidth = spriteBounds.width * scale.x;
            float barHeight = spriteBounds.height * scale.y;
            float barPosX = spriteEntity.value()->sprite.getPosition().x;
            float barPosY = spriteEntity.value()->sprite.getPosition().y;

            for (size_t i = 0; i < entity.textData.categorySize; i++) {
                std::string displayText = GameTextFactory(entity.textData.categoryTexts[i]);
                TextComponent textComponent(font, displayText, 0, 0, entity.textData.charSize);
                componentManager.addComponent<TextComponent>(
                    entity.textData.categoryIds[i], textComponent);

                if (auto textComponent = componentManager.getComponent<TextComponent>(
                        entity.textData.categoryIds[i])) {
                    sf::FloatRect textBounds = textComponent.value()->text.getLocalBounds();

                    float posX = barPosX;
                    if (entity.textData.categoryTexts[i] == GameText::Lives) {
                        posX -= (barWidth / 4);
                        displayText += std::to_string(entity.lives);
                    } else if (entity.textData.categoryTexts[i] == GameText::Score) {
                        posX += (barWidth / 4);
                        displayText += std::to_string(entity.score);
                    }
                    float posY =
                        barPosY - (barHeight / 2) + (barHeight / 2) - (textBounds.height / 2);

                    textComponent.value()->text.setPosition(posX, posY);
                    textComponent.value()->text.setString(displayText);
                }
            }
            sf::Vector2u newWindowSize = {
                windowSize.x, static_cast<unsigned int>(windowHeight - desiredHeight)};
            return newWindowSize;
        }
        return windowSize;
    }

    void updateInfoBar(UIEntityInformation entity, ComponentManager &componentManager)
    {
        for (size_t i = 0; i < entity.textData.categorySize; i++) {
            if (auto textComponent =
                    componentManager.getComponent<TextComponent>(entity.textData.categoryIds[i])) {
                std::string displayText = GameTextFactory(entity.textData.categoryTexts[i]);
                if (entity.textData.categoryTexts[i] == GameText::Lives) {
                    displayText += std::to_string(entity.lives);
                } else if (entity.textData.categoryTexts[i] == GameText::Score) {
                    displayText += std::to_string(entity.score);
                }
                textComponent.value()->text.setString(displayText);
            }
        }
    }

    void addEntity(EntityInformation entity, ComponentManager &componentManager,
        TextureManager &textureManager, sf::Vector2u windowSize)
    {
        if (entity.spriteData.type == AScenes::SpriteType::UI) {
            return;
        }
        float posX = windowSize.x * (entity.vPos.x / 100.0f);
        float posY = windowSize.y * (entity.vPos.y / 100.0f);
        float scaleX = (entity.ratio.x * windowSize.x) / entity.animationComponent.dimension.x;
        float scaleY = (entity.ratio.y * windowSize.y) / entity.animationComponent.dimension.y;
        sf::Texture &texture =
            textureManager.getTexture(SpriteFactory(entity.spriteData.spritePath));
        sf::Vector2f scale(scaleX, scaleY);
        sf::IntRect rect(entity.animationComponent.offset.x, entity.animationComponent.offset.y,
            entity.animationComponent.dimension.x, entity.animationComponent.dimension.y);
        SpriteComponent sprite(texture, posX, posY, scale, entity.spriteData.type, rect);
        componentManager.addComponent<SpriteComponent>(entity.uniqueID, sprite);
    }

    void removeEntity(int entityId, ComponentManager &componentManager)
    {
        componentManager.removeEntityFromComponent<SpriteComponent>(entityId);
    }

    void moveEntity(
        uint32_t id, vf2d newPos, ComponentManager &componentManager, sf::Vector2u windowSize)
    {
        auto spriteEntity = componentManager.getComponent<SpriteComponent>(id);
        if (spriteEntity) {
            float posX = windowSize.x * (newPos.x / 100.0f);
            float posY = windowSize.y * (newPos.y / 100.0f);
            spriteEntity.value()->sprite.setPosition(posX, posY);
        } else {
            std::cerr << "Entity not found, id: " << id << std::endl;
        }
    }

    void animateEntity(int entityId, AnimationComponent rect, ComponentManager &componentManager)
    {
        if (auto spritesOpt = componentManager.getComponentMap<SpriteComponent>()) {
            auto &sprites = **spritesOpt;
            auto entitySpriteIt = sprites.find(entityId);
            if (entitySpriteIt != sprites.end()) {
                auto &spriteComponent = entitySpriteIt->second;
                if (auto entitySprite = std::any_cast<SpriteComponent>(&spriteComponent)) {
                    sf::IntRect newRect(
                        rect.offset.x, rect.offset.y, rect.dimension.x, rect.dimension.y);
                    entitySprite->sprite.setTextureRect(newRect);
                }
            }
        }
    }

    void displayEndOfGame(ComponentManager &componentManager, TextureManager &textureManager,
        FontManager &fontManager, sf::Vector2u windowSize)
    {
        float yPos = 50;
        float xPos = windowSize.x / 2;
        sf::Font &font = fontManager.getFont(FontFactory(FontPath::MAIN));
        const std::string winText = "You Win!";
        TextComponent textComponent(font, winText, xPos, yPos, 80);
        componentManager.addComponent<TextComponent>(3, textComponent);

        std::vector<std::string> scores;
        std::ifstream file("GameScores/scores.txt");
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                scores.push_back(line);
            }
            file.close();
        } else {
            throw failedToOpenFile();
        }
        int id = 4;
        for (const auto &score : scores) {
            yPos += 50.0f;
            TextComponent textComponent(font, score, xPos, yPos, 50);
            componentManager.addComponent<TextComponent>(id, textComponent);
            id++;
        }
    }
};
} // namespace net
} // namespace r_type
