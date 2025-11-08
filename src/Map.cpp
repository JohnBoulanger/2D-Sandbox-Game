#include "Map.h"
#include "TileConstants.h"

Map::Map(int size)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    map = std::vector<std::vector<int>>(size, std::vector<int>(size, 0));

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            if (y == 0)
                map[y][x] = GRASS;
            else if (y > 0 && y <= 2)
                map[y][x] = DIRT;
            else
            {
                // mostly stone, occasional gold
                if (std::rand() % 100 < 5)
                    map[y][x] = GOLD;
                else
                    map[y][x] = STONE;
            }
        }
    }
}


Map::~Map()
{

}

void Map::PrintMap()
{
    // print map
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
}