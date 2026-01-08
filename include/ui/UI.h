#pragma once
#include <SFML/Graphics.hpp>
#include "HealthBar.h"
#include "Inventory.h"
#include "PauseMenu.h"

class UI
{
public:
    UI();
    ~UI();

    void update();
    void draw(sf::RenderWindow &window, sf::Vector2f mousePos);

private:
    sf::Font font;
    HealthBar healthBar;
    Inventory inventory;
    PauseMenu pauseMenu;
};