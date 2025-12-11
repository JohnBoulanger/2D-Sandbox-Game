#include "world/World.h"
#include "config/PhysicsConstants.h"
#include "config/PlayerConstants.h"
#include "config/MapConstants.h"
#include "core/TextureUtils.h"

World::World() :
    map(),
    playerTexture(loadTexture(PLAYER_PATH)),
    player(DEFAULT_PLAYER_STATE, playerTexture, {13, 4}, PLAYER_ANIMATION_SPEED, SPEED, JUMP_HEIGHT)
{
    map.printMap();
}

World::~World()
{

}

void World::update(sf::RenderWindow& window, float deltaTime)
{   
    // update map

    // update player
    player.update(deltaTime);
    handleCollisions(window);
}

void World::draw(sf::RenderWindow& window, sf::View& view)
{
    // draw map
    map.draw(window, view);

    // draw player
    player.draw(window);
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

