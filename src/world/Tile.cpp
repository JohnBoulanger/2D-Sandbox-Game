#include "world/Tile.h"
#include "systems/Collider.h"

Tile::Tile(sf::Texture& texture, TileID id, sf::Vector2f size, sf::Vector2f position) :
    collider(hitbox)
{
    this->id = id;

    // todo: change this eventually
    this->option = rand() % 3;

    // sprite setup
    body.setOrigin(size * 0.5f);
    body.setTexture(texture);
    body.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
    body.setPosition({floor(position.x), floor(position.y)});

    if (id > 0)
    {
        hitbox.setSize(size);
        hitbox.setOrigin(size * 0.5f);
        hitbox.setPosition(position);
        hitbox.setOutlineThickness(1.0f);
        hitbox.setOutlineColor(sf::Color::Blue);
        hitbox.setFillColor(sf::Color::Transparent);
    }
}

Tile::~Tile() {}

void Tile::draw(sf::RenderWindow& window, int bitmask)
{
    std::pair<int, int> spriteCoordinates = bitmaskToTile.at(bitmask)[option];
    sf::IntRect tileSprite(
        spriteCoordinates.first * TILE_SIZE + 2 * spriteCoordinates.first,
        spriteCoordinates.second * TILE_SIZE + 2 * spriteCoordinates.second,
        TILE_SIZE,
        TILE_SIZE
    );
    body.setTextureRect(tileSprite);
    window.draw(body);
    //window.draw(hitbox);
}

void Tile::setTile(sf::Texture& texture, TileID newId)
{
    id = newId;
    body.setTexture(texture, true);

    if (newId > 0)
    {
        hitbox.setSize({TILE_SIZE, TILE_SIZE});
        hitbox.setOrigin({TILE_SIZE * 0.5f, TILE_SIZE * 0.5f});
        hitbox.setPosition(body.getPosition());
        hitbox.setOutlineThickness(1.0f);
        hitbox.setOutlineColor(sf::Color::Blue);
        hitbox.setFillColor(sf::Color::Transparent);
    }
    else
    {
        hitbox.setSize({0.f, 0.f});
    }
}