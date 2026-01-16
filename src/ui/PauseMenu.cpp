#include "ui/PauseMenu.h"
#include "core/GameState.h"
#include <iostream>

PauseMenu::PauseMenu(GameState& gameState, const sf::Vector2f& windowSize)
: gameState(gameState)
{
    // Load font
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cerr << "Failed to load font\n";
    }

    // === Overlay ===
    overlay.setSize(windowSize);
    overlay.setFillColor(sf::Color(0, 0, 0, 160));

    // === Panel ===
    panel.setSize({360.f, 260.f});
    panel.setFillColor(sf::Color(40, 40, 40, 230));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(180, 180, 180));
    panel.setPosition(
        windowSize.x * 0.5f - panel.getSize().x * 0.5f,
        windowSize.y * 0.5f - panel.getSize().y * 0.5f
    );

    // === Title ===
    titleText.setFont(font);
    titleText.setString("Paused");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::White);

    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(
        titleBounds.left + titleBounds.width / 2.f,
        titleBounds.top + titleBounds.height / 2.f
    );
    titleText.setPosition(
        panel.getPosition().x + panel.getSize().x / 2.f,
        panel.getPosition().y + 40.f
    );

    // === Resume Button ===
    resumeButton.setSize({220.f, 60.f});
    resumeButton.setFillColor(sf::Color(70, 70, 70));
    resumeButton.setOutlineThickness(1.f);
    resumeButton.setOutlineColor(sf::Color::Black);
    resumeButton.setPosition(
        panel.getPosition().x + panel.getSize().x / 2.f - 110.f,
        panel.getPosition().y + 100.f
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

    // === Quit Button ===
    quitButton.setSize({220.f, 60.f});
    quitButton.setFillColor(sf::Color(90, 50, 50));
    quitButton.setOutlineThickness(1.f);
    quitButton.setOutlineColor(sf::Color::Black);
    quitButton.setPosition(
        panel.getPosition().x + panel.getSize().x / 2.f - 110.f,
        panel.getPosition().y + 170.f
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

    // Mouse position in UI coordinates
    sf::Vector2f mousePos =
        window.mapPixelToCoords(
            sf::Mouse::getPosition(window),
            uiView
        );

    // === Hover effects ===
    resumeButton.setFillColor(
        resumeButton.getGlobalBounds().contains(mousePos)
            ? sf::Color(90, 90, 90)
            : sf::Color(70, 70, 70)
    );

    quitButton.setFillColor(
        quitButton.getGlobalBounds().contains(mousePos)
            ? sf::Color(120, 60, 60)
            : sf::Color(90, 50, 50)
    );

    // === Click handling ===
    if (event.type == sf::Event::MouseButtonPressed)
    {
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
    window.draw(panel);
    window.draw(titleText);

    window.draw(resumeButton);
    window.draw(resumeText);

    window.draw(quitButton);
    window.draw(quitText);
}
