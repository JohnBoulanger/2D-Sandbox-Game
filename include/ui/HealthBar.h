#pragma once
#include <SFML/Graphics.hpp>

class HealthBar
{
public:
    HealthBar();
    ~HealthBar();

private:
    int health;
    sf::Texture healthTexture;

};