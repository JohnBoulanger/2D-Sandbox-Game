#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "entities/Player.h"

class World
{
public:
    World();
    ~World();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    sf::Vector2f GetPlayerPosition() { return player.GetPosition();}

private:
    //player
    sf::Texture playerTexture;
    Player player;
    //map
    Map map;
};