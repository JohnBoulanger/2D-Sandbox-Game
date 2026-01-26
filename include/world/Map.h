#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Map
{
public:
    Map();
    ~Map();

    void printMap();
    void draw(sf::RenderWindow& window, sf::View& view, sf::Vector2f mousePos);
    void update(float deltaTime, sf::Vector2f mousePos);
    void loadTileset();
    void generateHeightMap(std::vector<float>& noiseOutput, int width);
    void generateWorldNoise(std::vector<float>& noiseOutput, int width, int height);
    void handleEvent(sf::Event event);

    // getters
    Tile& getTile(int y, int x);

private:
    std::vector<sf::Texture> tileset;
    std::vector<std::vector<Tile>> map;

    bool placing = false;
};