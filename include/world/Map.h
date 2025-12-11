#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Map
{
public:
    Map();
    ~Map();

    void printMap();
    void draw(sf::RenderWindow& window, sf::View& view);
    void update();

    // getters
    Tile& getTile(int y, int x);

private:
    sf::Texture tileset;
    std::vector<std::vector<Tile>> map;
};