#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Map
{
public:
    Map(int size);
    ~Map();

    void PrintMap();
    void Draw(sf::RenderWindow& window);
    void Update();
    Tile GetTile(int i, int j) { return map[i][j]; }

private:
    std::vector<std::vector<Tile>> map;
    sf::Texture tileset;
};