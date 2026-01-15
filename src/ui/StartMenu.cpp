#include "ui/StartMenu.h"
#include "core/GameState.h"
#include <iostream>

StartMenu::StartMenu(GameState& gameState, const sf::Vector2f& windowSize)
: gameState(gameState)
{
    // Load font (adjust path if needed)
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    // Dark overlay
    overlay.setSize(windowSize);
    overlay.setFillColor(sf::Color(0, 0, 0, 160));

    // Start button
    startButton.setSize({220.f, 70.f});
    startButton.setFillColor(sf::Color(70, 70, 70));
    startButton.setPosition(
        windowSize.x * 0.5f - 110.f,
        windowSize.y * 0.5f - 35.f
    );

    // Button text
    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(28);
    startText.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = startText.getLocalBounds();
    startText.setOrigin(
        textBounds.left + textBounds.width / 2.f,
        textBounds.top + textBounds.height / 2.f
    );
    startText.setPosition(
        startButton.getPosition().x + startButton.getSize().x / 2.f,
        startButton.getPosition().y + startButton.getSize().y / 2.f
    );
}

void StartMenu::handleEvent(
    const sf::Event& event,
    sf::RenderWindow& window,
    sf::View& uiView
)
{
    if (!gameState.isInStartMenu())
        return;

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos =
            window.mapPixelToCoords(
                {event.mouseButton.x, event.mouseButton.y},
                uiView
            );

        if (startButton.getGlobalBounds().contains(mousePos)) {
            gameState.toggleStartMenu();
        }
    }
}


void StartMenu::draw(sf::RenderWindow& window)
{
    if (!gameState.isInStartMenu())
        return;

    window.draw(overlay);
    window.draw(startButton);
    window.draw(startText);
}
