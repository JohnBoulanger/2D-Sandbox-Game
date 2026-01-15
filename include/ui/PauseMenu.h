#pragma once
#include <SFML/Graphics.hpp>

class GameState;

class PauseMenu {
public:
    PauseMenu(GameState& gameState, const sf::Vector2f& windowSize);

    void handleEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        sf::View& uiView
    );

    void draw(sf::RenderWindow& window);

private:
    GameState& gameState;

    // Font
    sf::Font font;

    // Overlay
    sf::RectangleShape overlay;

    // Panel
    sf::RectangleShape panel;

    // Title
    sf::Text titleText;

    // Resume button
    sf::RectangleShape resumeButton;
    sf::Text resumeText;

    // Quit button
    sf::RectangleShape quitButton;
    sf::Text quitText;
};
