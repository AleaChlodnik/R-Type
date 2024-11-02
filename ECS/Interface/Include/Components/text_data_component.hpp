/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** text_data_component
*/

#pragma once

#include "../font_path.hpp"
#include "../game_text.hpp"

/**
 * @struct TextDataComponent
 * @brief Component that holds text-related data for an entity.
 *
 * This component is used to store information about text that can be rendered
 * in the game, including font path, character size, category IDs, and category texts.
 *
 * @var TextDataComponent::fontPath
 * Path to the font file used for rendering the text.
 *
 * @var TextDataComponent::charSize
 * Size of the characters to be rendered.
 *
 * @var TextDataComponent::categoryIds
 * Array of category IDs associated with the text.
 *
 * @var TextDataComponent::categoryTexts
 * Array of GameText objects representing the text for each category.
 *
 * @var TextDataComponent::categorySize
 * Number of categories available.
 */
struct TextDataComponent {
    FontPath fontPath;
    uint32_t charSize = 0;
    uint32_t categoryIds[5] = {0};
    GameText categoryTexts[5];
    uint32_t categorySize = 0;
};
