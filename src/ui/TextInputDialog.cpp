#include "ui/TextInputDialog.h"
#include <iostream>

TextInputDialog::TextInputDialog(const sf::Vector2f& windowSize, const std::string& prompt)
    : prompt(prompt), windowSize(windowSize)
{
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cerr << "Failed to load font for TextInputDialog\n";
    }

    // Semi-transparent background
    background.setSize(windowSize);
    background.setFillColor(sf::Color(0, 0, 0, 100));

    // Panel
    panel.setSize({400.f, 200.f});
    panel.setFillColor(sf::Color(40, 40, 40, 230));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(180, 180, 180));
    panel.setPosition(
        windowSize.x * 0.5f - panel.getSize().x * 0.5f,
        windowSize.y * 0.5f - panel.getSize().y * 0.5f
    );

    // Prompt text
    promptText.setFont(font);
    promptText.setString(prompt);
    promptText.setCharacterSize(18);
    promptText.setFillColor(sf::Color::White);
    promptText.setPosition(
        panel.getPosition().x + 20.f,
        panel.getPosition().y + 20.f
    );

    // Input display
    inputDisplay.setFont(font);
    inputDisplay.setString("");
    inputDisplay.setCharacterSize(20);
    inputDisplay.setFillColor(sf::Color::White);
    inputDisplay.setPosition(
        panel.getPosition().x + 20.f,
        panel.getPosition().y + 60.f
    );

    // Confirm button
    confirmButton.setSize({80.f, 40.f});
    confirmButton.setFillColor(sf::Color(70, 70, 70));
    confirmButton.setOutlineThickness(1.f);
    confirmButton.setOutlineColor(sf::Color::Black);
    confirmButton.setPosition(
        panel.getPosition().x + 100.f,
        panel.getPosition().y + 130.f
    );

    confirmText.setFont(font);
    confirmText.setString("OK");
    confirmText.setCharacterSize(16);
    confirmText.setFillColor(sf::Color::White);
    const sf::FloatRect confirmBounds = confirmText.getLocalBounds();
    confirmText.setOrigin(
        confirmBounds.left + confirmBounds.width * 0.5f,
        confirmBounds.top + confirmBounds.height * 0.5f
    );
    confirmText.setPosition(
        confirmButton.getPosition().x + confirmButton.getSize().x * 0.5f,
        confirmButton.getPosition().y + confirmButton.getSize().y * 0.5f
    );

    // Cancel button
    cancelButton.setSize({80.f, 40.f});
    cancelButton.setFillColor(sf::Color(70, 70, 70));
    cancelButton.setOutlineThickness(1.f);
    cancelButton.setOutlineColor(sf::Color::Black);
    cancelButton.setPosition(
        panel.getPosition().x + 220.f,
        panel.getPosition().y + 130.f
    );

    cancelText.setFont(font);
    cancelText.setString("Cancel");
    cancelText.setCharacterSize(16);
    cancelText.setFillColor(sf::Color::White);
    const sf::FloatRect cancelBounds = cancelText.getLocalBounds();
    cancelText.setOrigin(
        cancelBounds.left + cancelBounds.width * 0.5f,
        cancelBounds.top + cancelBounds.height * 0.5f
    );
    cancelText.setPosition(
        cancelButton.getPosition().x + cancelButton.getSize().x * 0.5f,
        cancelButton.getPosition().y + cancelButton.getSize().y * 0.5f
    );
}

void TextInputDialog::handleEvent(const sf::Event& event, sf::RenderWindow& window, sf::View& uiView)
{
    if (!active)
        return;

    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == 8) {  // Backspace
                if (!inputText.empty()) {
                    inputText.pop_back();
                }
            } else if (event.text.unicode == 13) {  // Enter
                confirmed = true;
                active = false;
            } else if (event.text.unicode >= 32 && event.text.unicode < 127) {  // Printable ASCII
                if (inputText.length() < 32) {  // Limit to 32 characters
                    inputText += static_cast<char>(event.text.unicode);
                }
            }
            updateInputDisplay();
        }
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
        const sf::Vector2f mousePos =
            window.mapPixelToCoords(
                {event.mouseButton.x, event.mouseButton.y},
                uiView
            );

        if (confirmButton.getGlobalBounds().contains(mousePos)) {
            confirmed = true;
            active = false;
        } else if (cancelButton.getGlobalBounds().contains(mousePos)) {
            active = false;
            inputText = "";
            confirmed = false;
        }
    }

    // Handle button hover effects
    const sf::Vector2f mousePos =
        window.mapPixelToCoords(sf::Mouse::getPosition(window), uiView);

    confirmButton.setFillColor(
        confirmButton.getGlobalBounds().contains(mousePos)
            ? sf::Color(90, 90, 90)
            : sf::Color(70, 70, 70)
    );

    cancelButton.setFillColor(
        cancelButton.getGlobalBounds().contains(mousePos)
            ? sf::Color(90, 90, 90)
            : sf::Color(70, 70, 70)
    );
}

void TextInputDialog::draw(sf::RenderWindow& window)
{
    if (!active)
        return;

    window.draw(background);
    window.draw(panel);
    window.draw(promptText);
    window.draw(inputDisplay);
    window.draw(confirmButton);
    window.draw(confirmText);
    window.draw(cancelButton);
    window.draw(cancelText);
}

void TextInputDialog::show()
{
    active = true;
    confirmed = false;
    inputText = "";
    updateInputDisplay();
}

void TextInputDialog::hide()
{
    active = false;
}

void TextInputDialog::reset()
{
    active = false;
    confirmed = false;
    inputText = "";
    updateInputDisplay();
}

void TextInputDialog::updateInputDisplay()
{
    inputDisplay.setString(inputText.empty() ? "_" : inputText);
}
