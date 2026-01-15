#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "ui/UI.h"
#include "entities/Player.h"

class GameState;

class World
{
public:
    World(GameState& gameState);
    ~World();

    void update(sf::RenderWindow& window, float deltaTime, sf::View& camera, sf::View& uiView);
    void handleCollisions(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::View& camera, sf::View& uiView);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window, sf::View& uiView);

    // getters
    sf::Vector2f getPlayerPosition() { return player.getPosition(); }

private:
    // player
    Player player;
    // map
    Map map;
    // ui
    UI ui;
    sf::Vector2i mousePixelPos;
    sf::Vector2f mousePos;
    // state
    GameState& gameState;
};