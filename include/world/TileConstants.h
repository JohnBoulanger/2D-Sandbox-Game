#include <SFML/Graphics.hpp>

enum TileID
{
    DIRT = 0,
    STONE = 1,
    GRASS = 2,
    GOLD = 3,
    WATER = 4
};

struct TileType {
    int id;
    sf::RectangleShape tileRect;
    bool solid;
    std::string name;
};

// all tiles 16px x 16px
constexpr float TILE_WIDTH = 16.0f;
constexpr float TILE_HEIGHT = 16.0f;