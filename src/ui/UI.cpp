#include <ui/UI.h>
#include <config/TileConstants.h>

UI::UI()
{

}

UI::~UI()
{

}

void UI::update()
{

}

void UI::draw(sf::RenderWindow& window, sf::Vector2f mousePos)
{
    healthBar.draw(window);
    inventory.draw(window);
}