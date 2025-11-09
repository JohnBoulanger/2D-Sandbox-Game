#include "world/Map.h"
#include "world/Tile.h"
#include "config/MapConstants.h"

Map::Map() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    tileset.loadFromFile("textures/Tileset.png");

    map.resize(MAP_HEIGHT);
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        map[y].reserve(MAP_WIDTH);
        for (int x = 0; x < MAP_WIDTH; ++x) {

            // choose a TileID
            TileID id;
            if (y == 0)
                id = GRASS;
            else if (y <= 2)
                id = DIRT;
            else
                id = (std::rand() % 100 < 5) ? GOLD : STONE;

            // world position (in pixels)
            sf::Vector2f position(x * TILE_WIDTH, y * TILE_HEIGHT);

            // construct directly in-place
            map[y].emplace_back(tileset, id,
                                sf::Vector2f(TILE_WIDTH, TILE_HEIGHT),
                                position);
        }
    }
}


Map::~Map()
{

}

void Map::Draw(sf::RenderWindow& window)
{
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x].Draw(window);
        }
    }
}

void Map::Update()
{

}

void Map::PrintMap()
{
    // print map
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            //printf("%d", map[i][j].);
        }
        //printf("\n");
    }
}

Tile Map::GetTile(int y, int x)
{
    return map[y][x];
}