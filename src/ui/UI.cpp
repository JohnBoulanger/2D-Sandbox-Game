#include <ui/UI.h>

UI::UI()
{

}

UI::~UI()
{

}

void UI::update()
{

}

void UI::draw(sf::RenderWindow& window)
{
    healthBar.draw(window);
    inventory.draw(window);
}