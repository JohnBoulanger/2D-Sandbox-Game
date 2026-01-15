#pragma once

#include <SFML/Graphics.hpp>
#include "HealthBar.h"
#include "Inventory.h"
#include "PauseMenu.h"
#include "StartMenu.h"

class GameState;

class UI {
public:
    UI(GameState& gameState);
    ~UI();

    void update();
    void draw(sf::RenderWindow& window, sf::Vector2f mousePos);

private:
    GameState& gameState;

    PauseMenu pauseMenu;
    StartMenu startMenu;

    HealthBar healthBar;
    Inventory inventory;
};
