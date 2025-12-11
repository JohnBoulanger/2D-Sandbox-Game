#pragma once
#include <SFML/Graphics.hpp>
#include "entities/Collider.h"
#include "config/TileConstants.h"

class Tile
{
public:
    Tile(sf::Texture& texture, TileID id, sf::Vector2f size, sf::Vector2f positon);
    ~Tile();

    void draw(sf::RenderWindow& window);

    // getters
    Collider& getCollider() { return collider; }

private:
    sf::Sprite body;
    sf::RectangleShape hitbox;
    Collider collider;
    TileID id;
    TileType type;
};