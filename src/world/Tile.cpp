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

    if (id != AIR)
    {
        hitbox.setSize(size);
        hitbox.setOrigin(size * 0.5f);
        hitbox.setPosition(position);
        hitbox.setOutlineThickness(1.0f);
        hitbox.setOutlineColor(sf::Color::Blue);
        hitbox.setFillColor(sf::Color::Transparent);
        solid = true;
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
    // window.draw(hitbox);
}

void Tile::setTile(sf::Texture& texture, TileID newId, int x, int y)
{
    id = newId;
    body.setTexture(texture, true);
    sf::Vector2f position(x * TILE_SIZE, y * TILE_SIZE);

    if (newId > 0)
    {
        hitbox.setSize({TILE_SIZE, TILE_SIZE});
        hitbox.setOrigin({TILE_SIZE * 0.5, TILE_SIZE * 0.5});
        hitbox.setPosition(position);
        hitbox.setOutlineThickness(1.0f);
        hitbox.setOutlineColor(sf::Color::Blue);
        hitbox.setFillColor(sf::Color::Transparent);
        solid = true;
    }
    else
    {    
        hitbox.setSize({0.f, 0.f});
        solid = false;
    }
}