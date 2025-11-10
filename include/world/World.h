#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "entities/Player.h"

class World
{
public:
    World();
    ~World();

    void Update(sf::RenderWindow& window, float deltaTime);
    void Draw(sf::RenderWindow& window, sf::View& view);

    // getters
    sf::Vector2f GetPlayerPosition() { return player.GetPosition(); }

    // helpers
    sf::Vector2i PixelToTileCoords(float p_x, float p_y);

private:
    //player
    sf::Texture playerTexture;
    Player player;
    //map
    Map map;
};