#include <SFML/Graphics.hpp>

enum TileID
{
    AIR = 0,
    GRASS = 1,
    DIRT = 2,
    STONE = 3,
    CLAY = 4,
    WATER = 5
};

struct TileType {
    int id;
    sf::RectangleShape tileRect;
    bool solid;
    std::string name;
};

inline const std::map<int, std::pair<int, int>> bitmaskToTile = {
    // 0b{west, south, east, north} -> {x, y} on spritesheet
    {0b0000, {4, 3}},  // no neighbors
    {0b0001, {4, 2}},  // bottom end
    {0b0010, {1, 3}},  // left end
    {0b0011, {1, 2}},  // bottom left corner
    {0b0100, {4, 0}},  // top end
    {0b0101, {4, 1}},  // vertical piece
    {0b0110, {1, 0}},  // top left corner
    {0b0111, {1, 1}},  // left edge
    {0b1000, {3, 3}},  // right end
    {0b1001, {3, 2}},  // bottom right corner
    {0b1010, {2, 3}},  // horizontal piece
    {0b1011, {3, 2}},  // bottom edge
    {0b1100, {3, 0}},  // top right corner
    {0b1101, {3, 1}},  // right edge
    {0b1110, {2, 0}},  // top edge
    {0b1111, {2, 1}}   // center piece
};

constexpr int TILE_SIZE = 8;