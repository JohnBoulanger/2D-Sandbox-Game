#include "world/World.h"
#include "config/GameConstants.h"
#include "core/TextureUtils.h"

World::World() :
    map(),
    player(DEFAULT_PLAYER_STATE, {PLAYER_ANIM_FRAMES, PLAYER_NUM_ANIMS}, PLAYER_ANIMATION_SPEED, SPEED, JUMP_HEIGHT)
{

}

World::~World()
{

}

void World::update(sf::RenderWindow& window, float deltaTime, sf::View& camera, sf::View& uiView)
{   
    // update map
    map.update(deltaTime);

    // update player
    player.update(deltaTime);
    handleCollisions(window);
    mousePixelPos = sf::Mouse::getPosition(window);
    mouseWorldPos = window.mapPixelToCoords(mousePixelPos, camera);
    mouseUIPos = window.mapPixelToCoords(mousePixelPos, uiView);
    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
    // {
    //     printf("Mouse X: %d, Mouse Y: %d", mousePos.x, mousePos.y);
    // }
}

void World::draw(sf::RenderWindow& window, sf::View& camera, sf::View& uiView)
{
    // draw map
    window.setView(camera);
    map.draw(window, camera, mouseWorldPos);

    // draw player
    player.draw(window);

    // draw UI
    window.setView(uiView);
    ui.draw(window, mouseUIPos);
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

