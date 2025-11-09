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

void World::Update(float deltaTime)
{        
    player.Update(deltaTime);

    sf::Vector2f direction;
    sf::Vector2i playerCoords = PixelToTileCoords(
        player.GetPosition().x, 
        player.GetPosition().y
    );
    // check nearby tiles for collisions
    for (int y = playerCoords.y; y < playerCoords.y + 3; ++y)
    {
        for (int x = playerCoords.x; x < playerCoords.x + 3; ++x)
        {
            if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT)
                continue;   

            Tile tile = map.GetTile(y, x);
            if (tile.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
                player.OnCollision(direction);
        }
    }
}


void World::Draw(sf::RenderWindow& window)
{
    map.Draw(window);
    player.Draw(window);
}

sf::Vector2i World::PixelToTileCoords(float p_x, float p_y)
{
    int t_x = static_cast<int>(p_x / TILE_WIDTH);
    int t_y = static_cast<int>(p_y / TILE_HEIGHT);
    return {t_x, t_y};
}
