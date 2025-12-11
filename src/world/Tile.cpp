#include "world/Tile.h"
#include "entities/Collider.h"

Tile::Tile(sf::Texture& texture, TileID id, sf::Vector2f size, sf::Vector2f position) :
    collider(hitbox)
{
    // sprite setup
    body.setOrigin(size / 2.f);
    body.setTexture(texture);
    body.setTextureRect(sf::IntRect(id * (texture.getSize().x / 6), 0, texture.getSize().x / 6, texture.getSize().y));
    body.setPosition(position);

    // hitbox matches logical tile size
    if (id > 0)
    {
        hitbox.setSize(size);
        hitbox.setOrigin(size / 2.f);
        hitbox.setPosition(position);
        hitbox.setOutlineThickness(1.0f);
        hitbox.setOutlineColor(sf::Color::Blue);
        hitbox.setFillColor(sf::Color::Transparent);
    }
}

Tile::~Tile() {}

void Tile::draw(sf::RenderWindow& window)
{
    window.draw(body);
    //window.draw(hitbox);
}
