#pragma once
#include <SFML/Graphics.hpp>
#include "world/World.h"
#include "View.h"
#include "GameState.h"


class Game
{
public:
    Game();
    ~Game();

    void run();
    
private:
    // game
    sf::RenderWindow window;
    sf::View camera;
    sf::View uiView;
    sf::Clock clock;

    // game state
    GameState gameState;
    
    // world
    World world;
};