#include "ui/StartMenu.h"
#include "core/GameState.h"
#include <iostream>
#include <algorithm>
#include <core/TextureUtils.h>

StartMenu::StartMenu(GameState& gameState, const sf::Vector2f& windowSize)
: gameState(gameState)
{
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    if (!backgroundTexture.loadFromFile("terrariaTextures/Background_11.png")) {
        std::cerr << "Failed to load background texture\n";
    }

    if (!skyTexture.loadFromFile("terrariaTextures/Background_0.png")) {
        std::cerr << "Failed to load sky texture\n";
    }
    
    applyCoverScaling(backgroundSprite, backgroundTexture, windowSize);

    skySprite.setTexture(skyTexture);
    const sf::Vector2u skySize = skyTexture.getSize();
    skySprite.setScale(windowSize.x / skySize.x, windowSize.y / skySize.y);
    skySprite.setPosition(0.f, 0.f);

    panel.setSize({360.f, 260.f});
    panel.setFillColor(sf::Color(40, 40, 40, 230));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(180, 180, 180));
    panel.setPosition(
        windowSize.x * 0.5f - panel.getSize().x * 0.5f,
        windowSize.y * 0.5f - panel.getSize().y * 0.5f
    );

    titleText.setFont(font);
    titleText.setString("Terraria Clone");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::White);

    const sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(
        titleBounds.left + titleBounds.width * 0.5f,
        titleBounds.top  + titleBounds.height * 0.5f
    );
    titleText.setPosition(
        panel.getPosition().x + panel.getSize().x * 0.5f,
        panel.getPosition().y + 50.f
    );

    startButton.setSize({220.f, 60.f});
    startButton.setFillColor(sf::Color(70, 70, 70));
    startButton.setOutlineThickness(1.f);
    startButton.setOutlineColor(sf::Color::Black);
    startButton.setPosition(
        panel.getPosition().x + panel.getSize().x * 0.5f - 110.f,
        panel.getPosition().y + 140.f
    );

    startText.setFont(font);
    startText.setString("Start Game");
    startText.setCharacterSize(26);
    startText.setFillColor(sf::Color::White);

    const sf::FloatRect textBounds = startText.getLocalBounds();
    startText.setOrigin(
        textBounds.left + textBounds.width * 0.5f,
        textBounds.top  + textBounds.height * 0.5f
    );
    startText.setPosition(
        startButton.getPosition().x + startButton.getSize().x * 0.5f,
        startButton.getPosition().y + startButton.getSize().y * 0.5f
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

    const sf::Vector2f mousePos =
        window.mapPixelToCoords(
            {event.mouseButton.x, event.mouseButton.y},
            uiView
        );

    const bool hovered =
        startButton.getGlobalBounds().contains(mousePos);

    startButton.setFillColor(
        hovered ? sf::Color(90, 90, 90)
                : sf::Color(70, 70, 70)
    );

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left &&
        hovered)
    {
        gameState.toggleStartMenu();
    }
}

void StartMenu::draw(sf::RenderWindow& window)
{
    if (!gameState.isInStartMenu())
        return;

    window.draw(skySprite);
    window.draw(backgroundSprite);
    window.draw(panel);
    window.draw(titleText);
    window.draw(startButton);
    window.draw(startText);
}
