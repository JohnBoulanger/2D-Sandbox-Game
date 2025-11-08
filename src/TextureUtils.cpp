#include "TextureUtils.h"
#include <stdexcept>

sf::Texture LoadTexture(const std::string& path)
{
    sf::Texture texture;
    if (!texture.loadFromFile(path))
        throw std::runtime_error("Failed to load texture: " + path);
    return texture;
}
