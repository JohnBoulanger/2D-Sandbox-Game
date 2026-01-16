#pragma once
#include <SFML/Graphics.hpp>
#include "systems/Collider.h"
#include "config/TileConstants.h"

class Tile
{
public:
    Tile(sf::Texture& texture, TileID id, sf::Vector2f size, sf::Vector2f positon);
    ~Tile();

    void draw(sf::RenderWindow& window, int bitmask);

    // getters
    Collider& getCollider() { return collider; }
    TileID getTileID() { return id; }
    bool isSolid() { return solid; }

    // setters
    void setTile(sf::Texture& texture, TileID id, int x, int y);

private:
    sf::Sprite body;
    sf::RectangleShape hitbox;
    Collider collider;
    TileID id;
    int option;
    TileType type;
    bool solid = false;
};