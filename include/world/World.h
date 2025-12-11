#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "ui/UI.h"
#include "entities/Player.h"

class World
{
public:
    World();
    ~World();

    void update(sf::RenderWindow& window, float deltaTime);
    void handleCollisions(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::View& view);

    // getters
    sf::Vector2f getPlayerPosition() { return player.getPosition(); }

private:
    // player
    Player player;
    // map
    Map map;
    // ui
    UI ui;
};