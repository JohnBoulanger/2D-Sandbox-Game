#include "core/TextureUtils.h"
#include <stdexcept>

sf::Texture loadTexture(const std::string& path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path))
        throw std::runtime_error("Failed to load texture: " + path);
    return texture;
}

void applyCoverScaling(
    sf::Sprite& sprite,
    const sf::Texture& texture,
    const sf::Vector2f& windowSize
)
{
    sprite.setTexture(texture);

    const sf::Vector2u texSize = texture.getSize();

    const float scale = std::max(
        windowSize.x / texSize.x,
        windowSize.y / texSize.y
    );

    sprite.setScale(scale, scale);
    sprite.setPosition(
        (windowSize.x - texSize.x * scale) * 0.5f,
        (windowSize.y - texSize.y * scale) * 0.5f
    );
}
