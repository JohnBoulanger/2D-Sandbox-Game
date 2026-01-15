#include "ui/PauseMenu.h"
#include "core/GameState.h"
#include <iostream>

PauseMenu::PauseMenu(GameState& gameState, const sf::Vector2f& windowSize)
: gameState(gameState)
{
    // Load font (adjust path if needed)
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    // Dark overlay
    overlay.setSize(windowSize);
    overlay.setFillColor(sf::Color(0, 0, 0, 160));

    // Resume button
    resumeButton.setSize({220.f, 60.f});
    resumeButton.setFillColor(sf::Color(70, 70, 70));
    resumeButton.setPosition(
        windowSize.x * 0.5f - 110.f,
        windowSize.y * 0.5f - 80.f
    );

    resumeText.setFont(font);
    resumeText.setString("Resume");
    resumeText.setCharacterSize(26);
    resumeText.setFillColor(sf::Color::White);

    sf::FloatRect resumeBounds = resumeText.getLocalBounds();
    resumeText.setOrigin(
        resumeBounds.left + resumeBounds.width / 2.f,
        resumeBounds.top + resumeBounds.height / 2.f
    );
    resumeText.setPosition(
        resumeButton.getPosition().x + resumeButton.getSize().x / 2.f,
        resumeButton.getPosition().y + resumeButton.getSize().y / 2.f
    );

    // Quit button
    quitButton.setSize({220.f, 60.f});
    quitButton.setFillColor(sf::Color(70, 70, 70));
    quitButton.setPosition(
        windowSize.x * 0.5f - 110.f,
        windowSize.y * 0.5f + 10.f
    );

    quitText.setFont(font);
    quitText.setString("Quit");
    quitText.setCharacterSize(26);
    quitText.setFillColor(sf::Color::White);

    sf::FloatRect quitBounds = quitText.getLocalBounds();
    quitText.setOrigin(
        quitBounds.left + quitBounds.width / 2.f,
        quitBounds.top + quitBounds.height / 2.f
    );
    quitText.setPosition(
        quitButton.getPosition().x + quitButton.getSize().x / 2.f,
        quitButton.getPosition().y + quitButton.getSize().y / 2.f
    );
}

void PauseMenu::handleEvent(
    const sf::Event& event,
    sf::RenderWindow& window,
    sf::View& uiView
)
{
    if (!gameState.isPaused())
        return;

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos =
            window.mapPixelToCoords(
                {event.mouseButton.x, event.mouseButton.y},
                uiView
            );

        if (resumeButton.getGlobalBounds().contains(mousePos)) {
            gameState.togglePause();
        }
        else if (quitButton.getGlobalBounds().contains(mousePos)) {
            std::exit(0);
        }
    }
}

void PauseMenu::draw(sf::RenderWindow& window)
{
    if (!gameState.isPaused())
        return;

    window.draw(overlay);
    window.draw(resumeButton);
    window.draw(resumeText);
    window.draw(quitButton);
    window.draw(quitText);
}
