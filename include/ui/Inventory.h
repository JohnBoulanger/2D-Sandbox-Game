#pragma once
#include <SFML/Graphics.hpp>
#include "InventorySlot.h"

class Inventory
{
public:
    Inventory();
    ~Inventory();

    void update();
    void draw(sf::RenderWindow& window);

private:
    int numInventorySlots = 8;
    std::vector<InventorySlot> inventorySlots;
};