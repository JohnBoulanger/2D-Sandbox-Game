#include "ui/UI.h"
#include "core/GameState.h"

UI::UI(GameState& gameState, const sf::Vector2f& windowSize)
: gameState(gameState),
  pauseMenu(gameState, windowSize),
  startMenu(gameState, windowSize),
  worldSelectMenu(gameState, windowSize)
{
}

void UI::handleEvent(const sf::Event& event, sf::RenderWindow& window, sf::View& uiView)
{
    // Start menu gets priority
    if (gameState.isInStartMenu()) {
        startMenu.handleEvent(event, window, uiView);
        return;
    }

    // World select menu
    if (gameState.isInWorldSelectMenu()) {
        worldSelectMenu.handleEvent(event, window, uiView);
        return;
    }

    // Pause menu input
    if (gameState.isPaused()) {
        pauseMenu.handleEvent(event, window, uiView);
    }
}

void UI::draw(sf::RenderWindow& window)
{
    // HUD (always visible when not in menus)
    if (!gameState.isInStartMenu() && !gameState.isInWorldSelectMenu()) {
        healthBar.draw(window);
        inventory.draw(window);
    }

    // Menus
    if (gameState.isInStartMenu()) {
        startMenu.draw(window);
    }
    else if (gameState.isInWorldSelectMenu()) {
        worldSelectMenu.draw(window);
    }
    else if (gameState.isPaused()) {
        pauseMenu.draw(window);
    }
}
