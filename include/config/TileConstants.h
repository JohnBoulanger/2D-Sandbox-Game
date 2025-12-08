#include <SFML/Graphics.hpp>

enum TileID
{
    AIR = 0,
    DIRT = 1,
    STONE = 2,
    GRASS = 3,
    GOLD = 4,
    WATER = 5
};

struct TileType {
    int id;
    sf::RectangleShape tileRect;
    bool solid;
    std::string name;
};

// all tiles 16px x 16px
constexpr int TILE_SIZE = 16;