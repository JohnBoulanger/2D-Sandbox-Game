#include "world/World.h"
#include "config/GameConstants.h"
#include "core/TextureUtils.h"
#include <core/GameState.h>
#include <core/View.h>
#include <iostream>

World::World(GameState& gameState)
: map()
, player(
      DEFAULT_PLAYER_STATE,
      {PLAYER_ANIM_FRAMES, PLAYER_NUM_ANIMS},
      PLAYER_ANIMATION_SPEED,
      SPEED,
      JUMP_HEIGHT
  )
, gameState(gameState)
, ui(gameState, {VIEW_WIDTH, VIEW_HEIGHT})
{
    const sf::Vector2f windowSize{VIEW_WIDTH, VIEW_HEIGHT};

    if (!backgroundTexture.loadFromFile("terrariaTextures/Background_11.png")) {
        std::cerr << "Failed to load background texture\n";
    }

    if (!skyTexture.loadFromFile("terrariaTextures/Background_0.png")) {
        std::cerr << "Failed to load sky texture\n";
    }

    applyCoverScaling(backgroundSprite, backgroundTexture, windowSize);

    skySprite.setTexture(skyTexture);
    const sf::Vector2u skySize = skyTexture.getSize();
    const float skyScaleX = windowSize.x / skySize.x;
    skySprite.setScale(skyScaleX, 1.f);
    skySprite.setPosition(
        (windowSize.x - skySize.x * skyScaleX) * 0.5f,
        0.f
    );
}


World::~World()
{

}

void World::update(sf::RenderWindow& window, float deltaTime, sf::View& camera, sf::View& uiView)
{   
    // update player and map when not paused
    if (!gameState.isPaused() && !gameState.isInStartMenu()) {
        // update map
        map.update(deltaTime);

        // update player
        player.update(deltaTime);
        handleCollisions(window);
        mousePixelPos = sf::Mouse::getPosition(window);
        mousePos = window.mapPixelToCoords(mousePixelPos, camera);
    };
    skySprite.setPosition(player.getPosition().x - window.getSize().x * 0.5f, player.getPosition().y - window.getSize().y * 0.5f);
    backgroundSprite.setPosition(player.getPosition().x - window.getSize().x * 0.5f, player.getPosition().y - window.getSize().y * 0.5f);
}

void World::draw(sf::RenderWindow& window, sf::View& camera, sf::View& uiView)
{
    // draw background
    window.setView(camera);
    window.draw(skySprite);
    window.draw(backgroundSprite);
    
    // draw map
    map.draw(window, camera, mousePos);

    // draw player
    player.draw(window);

    // draw UI
    window.setView(uiView);
    ui.draw(window);
}

void World::handleCollisions(sf::RenderWindow& window)
{
    sf::Vector2f direction;

    // todo: fix this after world gen applied
    sf::Vector2i playerCoords = {
        ((int)player.getPosition().x / TILE_SIZE) - 1,
        ((int)player.getPosition().y / TILE_SIZE) - 1
    };

    // check nearby tiles for collisions todo
    for (int x = playerCoords.x; x < playerCoords.x + 4; x++) {
        for (int y = playerCoords.y; y < playerCoords.y + 4; y++) {
            if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT)
                continue;

            Tile& tile = map.getTile(x, y);
            if (tile.getCollider().checkCollision(player.getCollider(), direction, 1.0f))
                player.onCollision(direction);
        }
    }
}

void World::handleEvent(const sf::Event& event, sf::RenderWindow& window, sf::View& uiView)
{
    ui.handleEvent(event, window, uiView);
}
