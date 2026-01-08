#include "ui/HealthBar.h"
#include <config/GameConstants.h>
#include <config/TileConstants.h>
#include <core/View.h>

HealthBar::HealthBar()
{
    health = 4;
    maxHealth = 5;
    hearts.resize(maxHealth);
    heartTexture.loadFromFile("terrariaTextures/UI/PlayerResourceSets/FancyClassic/HeartFill.png");
    emptyHeartTexture.loadFromFile("terrariaTextures/UI/PlayerResourceSets/FancyClassic/HeartEmpty.png");

    int padding = 20;
    int heartSize = 22;
    int heartSpacing = 2;
    float heartScale = 1.3f;

    for (int i = 0; i < maxHealth; i++) {

        if (i < health) {
            hearts[i].setTexture(&heartTexture);
        } else {
            hearts[i].setTexture(&emptyHeartTexture);
        }

        float healthBarX = VIEW_WIDTH - padding - (i + 1) * (heartSize + heartSpacing) * heartScale;
        float healthBarY = padding;

        hearts[i].setTextureRect(sf::IntRect(0, 0, heartSize, heartSize));
        hearts[i].setSize(sf::Vector2f(heartSize * heartScale, heartSize * heartScale));
        // todo: update dynamically with view size
        hearts[i].setPosition(healthBarX, healthBarY);
    }
}

HealthBar::~HealthBar()
{

}

void HealthBar::update()
{

}

void HealthBar::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < maxHealth; i++) {
        window.draw(hearts[i]);
    }
}