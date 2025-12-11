#include "ui/Inventory.h"
#include <config/GameConstants.h>
#include <config/TileConstants.h>
#include <core/View.h>

Inventory::Inventory()
{
    sf::Texture pickaxeTexture;
    sf::Texture dirtTexture;
    sf::Texture torchTexture;
    sf::Texture stoneTexture;
    sf::Texture swordTexture;
    sf::Texture woodTexture;
    sf::Texture axeTexture;
    sf::Texture emptyTexture;
    pickaxeTexture.loadFromFile("terrariaTextures/Pickaxe.png");
    axeTexture.loadFromFile("terrariaTextures/Axe.png");
    swordTexture.loadFromFile("terrariaTextures/Sword.png");
    dirtTexture.loadFromFile("terrariaTextures/DirtItem.png");
    stoneTexture.loadFromFile("terrariaTextures/StoneItem.png");
    woodTexture.loadFromFile("terrariaTextures/WoodItem.png");
    torchTexture.loadFromFile("terrariaTextures/Torch.png");
    emptyTexture.loadFromFile("terrariaTextures/EmptyItem.png");
    inventorySlots.reserve(numInventorySlots);
    inventorySlots.emplace_back(0, pickaxeTexture, pickaxeTexture.getSize());
    inventorySlots.emplace_back(1, axeTexture, axeTexture.getSize());
    inventorySlots.emplace_back(2, swordTexture, swordTexture.getSize());
    inventorySlots.emplace_back(3, dirtTexture, dirtTexture.getSize());
    inventorySlots.emplace_back(4, stoneTexture, stoneTexture.getSize());
    inventorySlots.emplace_back(5, woodTexture, woodTexture.getSize());
    inventorySlots.emplace_back(6, torchTexture, torchTexture.getSize());
    inventorySlots.emplace_back(7, emptyTexture, emptyTexture.getSize());
}

Inventory::~Inventory()
{

}

void Inventory::update()
{

}

void Inventory::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < numInventorySlots; i++) {
        inventorySlots[i].draw(window);
    }
}