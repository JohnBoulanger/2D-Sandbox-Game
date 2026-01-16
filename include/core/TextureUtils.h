#pragma once
#include <SFML/Graphics.hpp>
#include <string>

sf::Texture loadTexture(const std::string& path);

void applyCoverScaling(
    sf::Sprite& sprite,
    const sf::Texture& texture,
    const sf::Vector2f& windowSize
);
