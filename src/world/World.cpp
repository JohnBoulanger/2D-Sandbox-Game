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
    HandleCollisions();
}

void World::Draw(sf::RenderWindow& window, sf::View& view)
{
    // draw map
    map.Draw(window, view);

    // draw player
    player.Draw(window);
}

static sf::Vector2i pixelToTileCoords(float p_x, float p_y)
{
    int t_x = static_cast<int>(p_x / TILE_SIZE);
    int t_y = static_cast<int>(p_y / TILE_SIZE);
    return {t_x, t_y};
}

void World::HandleCollisions()
{
    sf::Vector2f direction;

    // todo: fix this after world gen applied
    sf::Vector2i playerCoords = pixelToTileCoords(
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

            // debugging for collision later
            // sf::RectangleShape blocksToCheck({TILE_SIZE, TILE_SIZE});
            // float px = static_cast<float>(playerCoords.x * 16);
            // float py = static_cast<float>(playerCoords.y * 16);
            // blocksToCheck.setPosition({px, py});
            // blocksToCheck.setFillColor(sf::Color::Blue);
            // window.draw(blocksToCheck);

            Tile tile = map.GetTile(y, x);
            if (tile.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
                player.OnCollision(direction);
        }
    }
}

