#include <FastNoise/FastNoise.h>
#include "world/Map.h"
#include "world/Tile.h"
#include "config/MapConstants.h"

static void generateNoise(std::vector<float>& noiseOutput, int width, int height);

Map::Map() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    tileset.loadFromFile("textures/Tileset.png");

    // use perlin noise to generate the map
    const int width = MAP_WIDTH;
    const int height = MAP_HEIGHT;
    std::vector<float> noiseOutput(width * height);
    generateNoise(noiseOutput, width, height);

    map.resize(MAP_WIDTH);
    for (int x = 0; x < MAP_WIDTH; x++) 
    {
        map[x].reserve(MAP_HEIGHT);
        for (int y = 0; y < MAP_HEIGHT; y++) 
        {
            TileID id = AIR;
            int sample = static_cast<int>((fabs(noiseOutput[x]) * 5) + 10);
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
                
            // world position (in pixels)
            sf::Vector2f position(x * TILE_SIZE, y * TILE_SIZE);

            // construct directly in-place
            map[x].emplace_back(tileset, id, sf::Vector2f(TILE_SIZE, TILE_SIZE), position);
        }
    }
}


Map::~Map()
{

}

void Map::Draw(sf::RenderWindow& window, sf::View& view)
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
            map[x][y].Draw(window);
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

Tile& Map::GetTile(int x, int y)
{
    return map[x][y];
}

static void generateNoise(std::vector<float>& noiseOutput, int width, int height)
{
    // Create and configure FastNoise generator
    FastNoise::SmartNode<> fnGenerator = FastNoise::NewFromEncodedNodeTree("DQAFAAAAAAAAQAgAAAAAAD8AAAAAAA==");

    fnGenerator->GenUniformGrid2D(
        noiseOutput.data(),
        0.5f, 0.5f,
        width, height,
        0.05f,
        rand()
    );

    FILE* fp = fopen("noise_output.txt", "w");
    if (!fp) return;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = i * width + j;
            fprintf(fp, "%f ", fabs(noiseOutput[index]) * 10);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}