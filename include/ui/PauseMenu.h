#pragma once

#include <SFML/Graphics.hpp>

class GameState;

class PauseMenu {
public:
    PauseMenu(GameState& gameState, const sf::Vector2f& windowSize);

    void handleEvent(const sf::Event& event, sf::RenderWindow& window, sf::View& uiView);
    void draw(sf::RenderWindow& window);

private:
    GameState& gameState;

    sf::RectangleShape overlay;
    sf::RectangleShape resumeButton;
    sf::RectangleShape quitButton;

    sf::Text resumeText;
    sf::Text quitText;
    sf::Font font;
};
