
#pragma once
#include <SFML/Graphics.hpp>

class InventorySlot
{
public:
    InventorySlot(int slotNum, sf::Texture& itemTexture, sf::Vector2u itemSize);
    ~InventorySlot();

    void update();
    void draw(sf::RenderWindow& window);

private:
    int slotNum;
    sf::Texture slotTexture;
    sf::Texture itemTexture;
    sf::RectangleShape inventorySlotBody;
    sf::RectangleShape inventoryItemBody;
};