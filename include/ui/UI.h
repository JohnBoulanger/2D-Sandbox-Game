#pragma once

#include <SFML/Graphics.hpp>

#include "HealthBar.h"
#include "Inventory.h"
#include "PauseMenu.h"
#include "StartMenu.h"

class GameState;

class UI {
public:
    UI(GameState& gameState, const sf::Vector2f& windowSize);

    // Forward SFML events to menus
    void handleEvent(const sf::Event& event, sf::RenderWindow& window, sf::View& uiView);

    // Draw everything UI-related
    void draw(sf::RenderWindow& window);

private:
    GameState& gameState;

    PauseMenu pauseMenu;
    StartMenu startMenu;

    // HUD
    HealthBar healthBar;
    Inventory inventory;
};
