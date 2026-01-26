#include "ui/WorldSelectMenu.h"
#include "core/GameState.h"
#include <iostream>
#include <algorithm>
#include <core/TextureUtils.h>

WorldSelectMenu::WorldSelectMenu(GameState& gameState, const sf::Vector2f& windowSize)
: gameState(gameState),
  textInputDialog(windowSize, "Enter World Name:")
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

    panel.setSize({500.f, 420.f});
    panel.setFillColor(sf::Color(40, 40, 40, 230));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(180, 180, 180));
    panel.setPosition(
        windowSize.x * 0.5f - panel.getSize().x * 0.5f,
        windowSize.y * 0.5f - panel.getSize().y * 0.5f
    );

    titleText.setFont(font);
    titleText.setString("Select World");
    titleText.setCharacterSize(32);
    titleText.setFillColor(sf::Color::White);

    const sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(
        titleBounds.left + titleBounds.width * 0.5f,
        titleBounds.top  + titleBounds.height * 0.5f
    );
    titleText.setPosition(
        panel.getPosition().x + panel.getSize().x * 0.5f,
        panel.getPosition().y + 25.f
    );

    // Setup 3 world slot buttons
    for (int i = 0; i < 3; i++) {
        slotButtons[i].setSize({280.f, 60.f});
        slotButtons[i].setFillColor(sf::Color(70, 70, 70));
        slotButtons[i].setOutlineThickness(1.f);
        slotButtons[i].setOutlineColor(sf::Color::Black);
        slotButtons[i].setPosition(
            panel.getPosition().x + panel.getSize().x * 0.5f - 140.f,
            panel.getPosition().y + 70.f + (i * 80.f)
        );

        slotTexts[i].setFont(font);
        slotTexts[i].setCharacterSize(18);
        slotTexts[i].setFillColor(sf::Color::White);
        slotTexts[i].setPosition(
            slotButtons[i].getPosition().x + 15.f,
            slotButtons[i].getPosition().y + 18.f
        );
    }

    // Back button
    backButton.setSize({280.f, 50.f});
    backButton.setFillColor(sf::Color(70, 70, 70));
    backButton.setOutlineThickness(1.f);
    backButton.setOutlineColor(sf::Color::Black);
    backButton.setPosition(
        panel.getPosition().x + panel.getSize().x * 0.5f - 140.f,
        panel.getPosition().y + 330.f
    );

    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(20);
    backText.setFillColor(sf::Color::White);

    const sf::FloatRect backBounds = backText.getLocalBounds();
    backText.setOrigin(
        backBounds.left + backBounds.width * 0.5f,
        backBounds.top  + backBounds.height * 0.5f
    );
    backText.setPosition(
        backButton.getPosition().x + backButton.getSize().x * 0.5f,
        backButton.getPosition().y + backButton.getSize().y * 0.5f
    );

    updateSlotDisplay();
}

void WorldSelectMenu::updateSlotDisplay()
{
    for (int i = 0; i < 3; i++) {
        if (worldManager.hasWorld(i)) {
            const WorldData& world = worldManager.getWorld(i);
            slotTexts[i].setString("Slot " + std::to_string(i + 1) + ": Load " + world.name);
        } else {
            slotTexts[i].setString("Slot " + std::to_string(i + 1) + ": Create World");
        }
    }
}

void WorldSelectMenu::handleEvent(
    const sf::Event& event,
    sf::RenderWindow& window,
    sf::View& uiView
)
{
    if (!gameState.isInWorldSelectMenu())
        return;

    // Handle text input dialog
    textInputDialog.handleEvent(event, window, uiView);

    if (textInputDialog.isActive()) {
        return;
    }

    // Check if text input was confirmed
    if (textInputDialog.wasConfirmed()) {
        int slot = gameState.getCreatingWorldSlot();
        if (slot >= 0 && slot < 3) {
            worldManager.createWorld(slot, textInputDialog.getInput());
            updateSlotDisplay();
        }
        textInputDialog.reset();
        gameState.setCreatingWorldSlot(-1);
        return;
    }

    const sf::Vector2f mousePos =
        window.mapPixelToCoords(
            {event.mouseButton.x, event.mouseButton.y},
            uiView
        );

    // Update button hover effects
    for (int i = 0; i < 3; i++) {
        slotButtons[i].setFillColor(
            slotButtons[i].getGlobalBounds().contains(mousePos)
                ? sf::Color(90, 90, 90)
                : sf::Color(70, 70, 70)
        );
    }

    backButton.setFillColor(
        backButton.getGlobalBounds().contains(mousePos)
            ? sf::Color(90, 90, 90)
            : sf::Color(70, 70, 70)
    );

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        // Check slot buttons
        for (int i = 0; i < 3; i++) {
            if (slotButtons[i].getGlobalBounds().contains(mousePos)) {
                if (worldManager.hasWorld(i)) {
                    // Load world - for now, just close menu
                    gameState.toggleWorldSelectMenu();
                } else {
                    // Create world - show text input
                    gameState.setCreatingWorldSlot(i);
                    textInputDialog.show();
                }
                return;
            }
        }

        // Check back button
        if (backButton.getGlobalBounds().contains(mousePos)) {
            gameState.toggleWorldSelectMenu();
            gameState.toggleStartMenu();
        }
    }
}

void WorldSelectMenu::draw(sf::RenderWindow& window)
{
    if (!gameState.isInWorldSelectMenu())
        return;

    window.draw(skySprite);
    window.draw(backgroundSprite);
    window.draw(panel);
    window.draw(titleText);
    
    for (int i = 0; i < 3; i++) {
        window.draw(slotButtons[i]);
        window.draw(slotTexts[i]);
    }
    
    window.draw(backButton);
    window.draw(backText);

    // Draw text input dialog if active
    textInputDialog.draw(window);
}

