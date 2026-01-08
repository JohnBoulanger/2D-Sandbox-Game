#pragma once
#include <SFML/Graphics.hpp>

class HealthBar
{
public:
    HealthBar();
    ~HealthBar();

    void update();
    void draw(sf::RenderWindow& window);

private:
    int health;
    int maxHealth;
    sf::Texture heartTexture;
    sf::Texture emptyHeartTexture;
    std::vector<sf::RectangleShape> hearts;
};