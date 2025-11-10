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
            sf::Vector2f position(x * TILE_SIZE, y * TILE_SIZE);

            // construct directly in-place
            map[y].emplace_back(tileset, id,
                                sf::Vector2f(TILE_SIZE, TILE_SIZE),
                                position);
        }
    }
}


Map::~Map()
{

}

void Map::Draw(sf::RenderWindow& window, sf::View& view)
{
    sf::Vector2f centre = view.getCenter();
    sf::Vector2f size = view.getSize();

    // only draw tiles within the view
    int leftTile   = std::clamp(static_cast<int>(floor((centre.x - size.x / 2.f) / TILE_SIZE)), 0, MAP_WIDTH  - 1);
    int rightTile  = std::clamp(static_cast<int>(ceil((centre.x + size.x / 2.f) / TILE_SIZE) + 1), 0, MAP_WIDTH  - 1);
    int topTile    = std::clamp(static_cast<int>(floor((centre.y - size.y / 2.f) / TILE_SIZE)), 0, MAP_HEIGHT - 1);
    int bottomTile = std::clamp(static_cast<int>(ceil((centre.y + size.y / 2.f) / TILE_SIZE) + 1), 0, MAP_HEIGHT - 1);
    
    for (int y = topTile; y < bottomTile; y++) {
        // iterate over each "y-layer"
        for (int x = leftTile; x < rightTile; x++) {
            map[y][x].Draw(window);
        }
    }
}

void Map::Update()
{

}

void Map::PrintMap()
{
    return;
}

Tile Map::GetTile(int y, int x)
{
    return map[y][x];
}