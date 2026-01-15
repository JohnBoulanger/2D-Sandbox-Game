#pragma once
#include <SFML/Graphics.hpp>

class GameState;

class StartMenu {
public:
    StartMenu(GameState& gameState);

    void show(sf::RenderWindow& window);
    void hide();

private:
    GameState& gameState;
};
