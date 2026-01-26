#pragma once
#include <SFML/Graphics.hpp>
#include "TextInputDialog.h"
#include "world/WorldManager.h"

class GameState;

class WorldSelectMenu {
public:
    WorldSelectMenu(GameState& gameState, const sf::Vector2f& windowSize);

    void handleEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        sf::View& uiView
    );

    void draw(sf::RenderWindow& window);

private:
    GameState& gameState;
    WorldManager worldManager;
    TextInputDialog textInputDialog;

    // menu
    sf::Font font;
    sf::RectangleShape panel;
    sf::Text titleText;
    
    // world slot buttons (3 slots)
    sf::RectangleShape slotButtons[3];
    sf::Text slotTexts[3];
    
    // back button
    sf::RectangleShape backButton;
    sf::Text backText;

    // background
    sf::Texture skyTexture;
    sf::Sprite skySprite;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    void updateSlotDisplay();
};

