#pragma once
#include <SFML/Graphics.hpp>
#include<Collider.h>

class Platform
{
public:
    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f positon);
    ~Platform();

    void Draw(sf::RenderWindow& window);
    Collider& GetCollider() { return collider; }

private:
    sf::RectangleShape body;
    Collider collider;
};