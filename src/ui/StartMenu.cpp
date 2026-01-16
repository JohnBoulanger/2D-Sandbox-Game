#include "ui/StartMenu.h"
#include "core/GameState.h"
#include <iostream>

StartMenu::StartMenu(GameState& gameState, const sf::Vector2f& windowSize)
: gameState(gameState)
{
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    // Dark overlay
    overlay.setSize(windowSize);
    overlay.setFillColor(sf::Color(0, 0, 0, 160));

    // Center panel
    panel.setSize({360.f, 260.f});
    panel.setFillColor(sf::Color(40, 40, 40, 230));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(180, 180, 180));
    panel.setPosition(
        windowSize.x * 0.5f - panel.getSize().x * 0.5f,
        windowSize.y * 0.5f - panel.getSize().y * 0.5f
    );

    // Title
    titleText.setFont(font);
    titleText.setString("Terraria Clone");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::White);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(
        titleBounds.left + titleBounds.width / 2.f,
        titleBounds.top + titleBounds.height / 2.f
    );
    titleText.setPosition(
        panel.getPosition().x + panel.getSize().x / 2.f,
        panel.getPosition().y + 50.f
    );

    // Start button
    startButton.setSize({220.f, 60.f});
    startButton.setFillColor(sf::Color(70, 70, 70));
    startButton.setOutlineThickness(1.f);
    startButton.setOutlineColor(sf::Color::Black);
    startButton.setPosition(
        panel.getPosition().x + panel.getSize().x / 2.f - 110.f,
        panel.getPosition().y + 140.f
    );

    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(26);
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

    sf::Vector2f mousePos =
    window.mapPixelToCoords(
        {event.mouseButton.x, event.mouseButton.y},
        uiView
    );

    startButton.setFillColor(
        startButton.getGlobalBounds().contains(mousePos)
                ? sf::Color(90, 90, 90)
                : sf::Color(70, 70, 70)
    );

    if (event.type == sf::Event::MouseButtonPressed)
    {
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
    window.draw(panel);
    window.draw(titleText);
    window.draw(startButton);
    window.draw(startText);
}
