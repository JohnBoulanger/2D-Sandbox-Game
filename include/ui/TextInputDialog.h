#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextInputDialog {
public:
    TextInputDialog(const sf::Vector2f& windowSize, const std::string& prompt = "Enter text:");

    void handleEvent(const sf::Event& event, sf::RenderWindow& window, sf::View& uiView);
    void draw(sf::RenderWindow& window);

    bool isActive() const { return active; }
    bool wasConfirmed() const { return confirmed; }
    const std::string& getInput() const { return inputText; }

    void show();
    void hide();
    void reset();

private:
    bool active = false;
    bool confirmed = false;
    std::string inputText;
    std::string prompt;

    sf::Font font;
    sf::RectangleShape background;
    sf::RectangleShape panel;
    sf::Text promptText;
    sf::Text inputDisplay;
    
    sf::RectangleShape confirmButton;
    sf::Text confirmText;
    
    sf::RectangleShape cancelButton;
    sf::Text cancelText;

    sf::Vector2f windowSize;
    
    void updateInputDisplay();
};
