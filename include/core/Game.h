#pragma once
#include <SFML/Graphics.hpp>
#include "world/World.h"
#include "View.h"


class Game
{
public:
    Game();
    ~Game();

    void Run();
    

private:
    // game
    sf::RenderWindow window;
    sf::View view;
    sf::Clock clock;
    // world
    World world;
};