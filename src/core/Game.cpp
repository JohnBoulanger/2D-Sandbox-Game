#include "core/Game.h"
#include "config/GameConstants.h"
#include "config/PhysicsConstants.h"
#include "config/PlayerConstants.h"
#include "core/TextureUtils.h"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close | sf::Style::Resize),
      view({0.0f, 0.0f}, {VIEW_WIDTH, VIEW_HEIGHT}),
      map(MAP_SIZE),
      platform(nullptr, {400.f, 200.f}, {400.f, 330.f}),
      playerTexture(LoadTexture(PLAYER_PATH)),
      player(DEFAULT_PLAYER_STATE, playerTexture, {PLAYER_SPRITESHEET_WIDTH, PLAYER_SPRITESHEET_HEIGHT}, PLAYER_ANIMATION_SPEED, SPEED, JUMP_HEIGHT)
{

}


Game::~Game()
{

}

void Game::Run()
{
    map.PrintMap();
    // core game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    ResizeView(window, view);
                default:
                    break;
            }
        }
        Update();
        Draw();
    }
}

void Game::Update()
{
    // create maximum delta time so resizing doesnt cause collision issues
    float deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20.0f)
            deltaTime = 1.0f / 20.0f;
        
    player.Update(deltaTime);
    sf::Vector2f direction;
    if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 0.0f))
        player.OnCollision(direction);

    view.setCenter(player.GetPosition());
}

void Game::Draw()
{
    window.clear();
    window.setView(view);
    player.Draw(window);
    platform.Draw(window);
    window.display();
}