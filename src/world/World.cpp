#include "world/World.h"
#include "config/GameConstants.h"
#include "config/PhysicsConstants.h"
#include "config/PlayerConstants.h"
#include "core/TextureUtils.h"

World::World() :
    map(MAP_SIZE),
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
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            if (map.GetTile(i,j).GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
                player.OnCollision(direction);
        }
    }
}

void World::Draw(sf::RenderWindow& window)
{
    map.Draw(window);
    player.Draw(window);
}