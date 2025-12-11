#include <FastNoise/FastNoise.h>
#include "world/Map.h"
#include "world/Tile.h"
#include "config/MapConstants.h"

static void generateHeightMap(std::vector<float>& noiseOutput, int width);
static void generateWorldNoise(std::vector<float>& noiseOutput, int width, int height);


Map::Map() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    tileset.loadFromFile("textures/Tileset.png");
    const int width = MAP_WIDTH;
    const int height = MAP_HEIGHT;
    std::vector<float> heightMap(width);
    std::vector<float> worldNoise(width * height);
    generateHeightMap(heightMap, width);
    generateWorldNoise(worldNoise, width, height);

    map.resize(MAP_WIDTH);
    for (int x = 0; x < MAP_WIDTH; x++) 
    {
        map[x].reserve(MAP_HEIGHT);
        for (int y = 0; y < MAP_HEIGHT; y++) 
        {
            TileID id = AIR;
            int sample = static_cast<int>((fabs(heightMap[x]) * 30) + GROUND_TO_TOP);
            if (sample <= y)
            {
                if(sample == y)
                {
                    id = GRASS;
                }
                else if (sample + 3 > y)
                {
                    id = DIRT;
                }
                else
                {
                    int r = (std::rand() % 15);
                    if (r == 0)
                    {
                        id = GOLD;
                    }
                    else
                    {
                        id = STONE;
                    }
                }
            }
            sf::Vector2f position(x * TILE_SIZE, y * TILE_SIZE);
            map[x].emplace_back(tileset, id, sf::Vector2f(TILE_SIZE, TILE_SIZE), position);
        }
    }
}


Map::~Map()
{

}

void Map::draw(sf::RenderWindow& window, sf::View& view)
{
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    // only draw tiles within the view
    int leftTile = std::clamp(static_cast<int>(floor((center.x - size.x / 2.f) / TILE_SIZE)), 0, MAP_WIDTH - 1);
    int rightTile = std::clamp(static_cast<int>(ceil((center.x + size.x / 2.f) / TILE_SIZE) + 1), 0, MAP_WIDTH - 1);
    int topTile = std::clamp(static_cast<int>(floor((center.y - size.y / 2.f) / TILE_SIZE)), 0, MAP_HEIGHT - 1);
    int bottomTile = std::clamp(static_cast<int>(ceil((center.y + size.y / 2.f) / TILE_SIZE) + 1), 0, MAP_HEIGHT - 1);
    
    for (int x = leftTile; x < rightTile; x++) {
        for (int y = topTile; y < bottomTile; y++) {
            map[x][y].draw(window);
        }
    }
}

void Map::update()
{

}

void Map::printMap()
{
    return;
}

Tile& Map::getTile(int x, int y)
{
    return map[x][y];
}

static void generateHeightMap(std::vector<float>& noiseOutput, int width)
{
    // Create and configure FastNoise generator
    FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("DQAFAAAAAAAAQAgAAAAAAD8AAAAAAA==");

    fnGenerator->GenUniformGrid2D(
        noiseOutput.data(),
        0, 0,
        width, 1,
        0.005f,
        rand()
    );

    FILE* fp = fopen("heightmap.txt", "w");
    if (!fp) return;

    for (int i = 0; i < width; i++) {
        fprintf(fp, "%f ", noiseOutput[i]);
    }

    fclose(fp);
}

static void generateWorldNoise(std::vector<float>& noiseOutput, int width, int height)
{
    // Create and configure FastNoise generator
    FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("DQAFAAAAAAAAQAgAAAAAAD8AAAAAAA==");

    fnGenerator->GenUniformGrid2D(
        noiseOutput.data(),
        0, 0,
        width, height,
        0.05f,
        rand()
    );

    FILE* fp = fopen("worldnoise.txt", "w");
    if (!fp) return;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width + j;
            fprintf(fp, "%f ", noiseOutput[index]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}