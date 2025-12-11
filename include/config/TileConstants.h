#include <SFML/Graphics.hpp>

enum TileID
{
    AIR = 0,
    GRASS = 1,
    DIRT = 2,
    STONE = 3,
    IRON = 4,
    WATER = 5
};

struct TileType {
    int id;
    sf::RectangleShape tileRect;
    bool solid;
    std::string name;
};

inline const std::map<int, std::vector<std::pair<int, int>>> bitmaskToTile = {
    // 0b{west, south, east, north} -> {x, y} on spritesheet
    {0b0000, {{9, 3}, {10, 3}, {11, 3}}},  // no neighbors
    {0b0001, {{6, 3}, {7, 3}, {8, 3}}},  // bottom end
    {0b0010, {{9, 0}, {9, 1}, {9, 2}}},  // left end
    {0b0011, {{0, 4}, {2, 4}, {4, 4}}},  // bottom left corner
    {0b0100, {{6, 0}, {7, 0}, {8, 0}}},  // top end
    {0b0101, {{5, 0}, {5, 1}, {5, 2}}},  // vertical piece
    {0b0110, {{0, 3}, {2, 3}, {4, 3}}},  // top left corner
    {0b0111, {{0, 0}, {0, 1}, {0, 2}}},  // left edge
    {0b1000, {{12, 0}, {12, 1}, {12, 2}}},  // right end
    {0b1001, {{1, 4}, {3, 4}, {5, 4}}},  // bottom right corner
    {0b1010, {{6, 4}, {7, 4}, {8, 4}}},  // horizontal piece
    {0b1011, {{1, 2}, {2, 2}, {3, 2}}},  // bottom edge
    {0b1100, {{1, 3}, {3, 3}, {5, 3}}},  // top right corner
    {0b1101, {{4, 0}, {4, 1}, {4, 2}}},  // right edge
    {0b1110, {{1, 0}, {2, 0}, {3, 0}}},  // top edge
    {0b1111, {{1, 1}, {2, 1}, {3, 1}}}   // center piece
};

constexpr int TILE_SIZE = 16;