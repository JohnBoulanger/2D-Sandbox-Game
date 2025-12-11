#include "ui/InventorySlot.h"
#include <config/GameConstants.h>
#include <config/TileConstants.h>
#include <core/View.h>

InventorySlot::InventorySlot(int slotNum, sf::Texture& itemTexture, sf::Vector2u itemSize)
{
    slotTexture.loadFromFile("terrariaTextures/InventorySlot.png");
    this->itemTexture = itemTexture;

    // slot parameters
    int padding = 12;
    int inventorySlotSize = 52;
    int inventorySlotSpacing = 4;
    float inventorySlotScale = 0.85f;
    float scaledSlotSize = inventorySlotSize * inventorySlotScale;
    int slotX = padding + slotNum * (inventorySlotSize + inventorySlotSpacing) * inventorySlotScale;
    int slotY = padding;

    // item parameters
    // center the item within the slot
    float itemX = slotX + (scaledSlotSize - itemSize.x) * 0.5f;
    float itemY = slotY + (scaledSlotSize - itemSize.y) * 0.5f;

    // slot texture
    inventorySlotBody.setTexture(&slotTexture);
    inventorySlotBody.setTextureRect(sf::IntRect(0, 0, inventorySlotSize, inventorySlotSize));
    inventorySlotBody.setSize(sf::Vector2f(scaledSlotSize, scaledSlotSize));
    inventorySlotBody.setPosition(slotX, padding);

    // item texture
    inventoryItemBody.setTexture(&this->itemTexture);
    inventoryItemBody.setTextureRect(sf::IntRect(0, 0, itemSize.x, itemSize.y));
    inventoryItemBody.setSize(sf::Vector2f(itemSize.x, itemSize.y));
    inventoryItemBody.setPosition(itemX, itemY);
}

InventorySlot::~InventorySlot()
{

}

void InventorySlot::update()
{

}

void InventorySlot::draw(sf::RenderWindow& window)
{
    window.draw(inventorySlotBody);
    window.draw(inventoryItemBody);
}