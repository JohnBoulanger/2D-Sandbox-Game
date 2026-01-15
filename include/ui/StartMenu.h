#pragma once
#include <SFML/Graphics.hpp>

class GameState;

class StartMenu {
public:
    StartMenu(GameState& gameState, const sf::Vector2f& windowSize);

    void handleEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        sf::View& uiView
    );

    void draw(sf::RenderWindow& window);

private:
    GameState& gameState;

    sf::Font font;

    sf::RectangleShape overlay;
    sf::RectangleShape panel;

    sf::Text titleText;

    sf::RectangleShape startButton;
    sf::Text startText;
};
