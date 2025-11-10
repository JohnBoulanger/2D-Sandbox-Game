#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Map
{
public:
    Map();
    ~Map();

    void PrintMap();
    void Draw(sf::RenderWindow& window, sf::View& view);
    void Update();

    // getters
    Tile GetTile(int y, int x);

private:
    sf::Texture tileset;
    std::vector<std::vector<Tile>> map;
};