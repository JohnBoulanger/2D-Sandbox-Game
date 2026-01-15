#include <ui/UI.h>
#include <config/TileConstants.h>
#include <core/GameState.h>

UI::UI(GameState& gameState) :
    gameState(gameState),
    pauseMenu(gameState),
    startMenu(gameState)
{

}

UI::~UI()
{

}

void UI::update()
{

}

void UI::draw(sf::RenderWindow& window, sf::Vector2f mousePos)
{
    // HUD (SFML)
    healthBar.draw(window);
    inventory.draw(window);

    // Menus (TGUI)
    if (gameState.isPaused()) {
        pauseMenu.show(window);
        startMenu.hide();
    } else if (gameState.isInStartMenu()) {
        startMenu.show(window);
        pauseMenu.hide();
    } else {
        pauseMenu.hide();
        startMenu.hide();
    }
}