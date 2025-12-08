#include "world/World.h"
#include "config/PhysicsConstants.h"
#include "config/PlayerConstants.h"
#include "config/MapConstants.h"
#include "core/TextureUtils.h"

World::World() :
    map(),
    playerTexture(LoadTexture(PLAYER_PATH)),
    player(DEFAULT_PLAYER_STATE, playerTexture, {13, 4}, PLAYER_ANIMATION_SPEED, SPEED, JUMP_HEIGHT)
{
    map.PrintMap();
}

World::~World()
{

}

void World::Update(sf::RenderWindow& window, float deltaTime)
{   
    // update map

    // update player
    player.Update(deltaTime);
    HandleCollisions(window);
}

void World::Draw(sf::RenderWindow& window, sf::View& view)
{
    // draw map
    map.Draw(window, view);

    // draw player
    player.Draw(window);
}

void World::HandleCollisions(sf::RenderWindow& window)
{
    sf::Vector2f direction;

    // todo: fix this after world gen applied
    sf::Vector2i playerCoords = {
        ((int)player.GetPosition().x / TILE_SIZE) - 1,
        ((int)player.GetPosition().y / TILE_SIZE) - 1
    };

    // check nearby tiles for collisions
    for (int x = playerCoords.x; x < playerCoords.x + 4; x++) {
        for (int y = playerCoords.y; y < playerCoords.y + 4; y++) {
            if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT)
                continue;

            Tile& tile = map.GetTile(x, y);
            if (tile.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
                player.OnCollision(direction);
        }
    }
}

