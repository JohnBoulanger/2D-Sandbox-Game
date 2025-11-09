#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Map
{
public:
    Map();
    ~Map();

    void PrintMap();
    void Draw(sf::RenderWindow& window);
    void Update();
    Tile GetTile(int y, int x);

private:
    std::vector<std::vector<Tile>> map;
    sf::Texture tileset;
};