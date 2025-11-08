#pragma once
#include <SFML/Graphics.hpp>
#include "entities/Player.h"
#include "world/Map.h"
#include "entities/Platform.h"
#include "View.h"


class Game
{
public:
    Game();
    ~Game();

    void Run();
    void Update();
    void Draw();

private:
    // game
    sf::RenderWindow window;
    sf::View view;
    sf::Clock clock;
    //player
    sf::Texture playerTexture;
    Player player;
    //map
    Map map;
    Platform platform;
};