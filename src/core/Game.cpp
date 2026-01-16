#include "core/Game.h"
#include "config/GameConstants.h"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close | sf::Style::Resize),
      camera({0.0f, 0.0f}, {VIEW_WIDTH, VIEW_HEIGHT}),
      uiView({0.0f, 0.0f}, {VIEW_WIDTH, VIEW_HEIGHT}),
      world(gameState) 
{
    uiView.setCenter(VIEW_WIDTH * 0.5f, VIEW_HEIGHT * 0.5f);
}

Game::~Game()
{

}

void Game::run()
{
    while (window.isOpen())
    {
        // create maximum delta time so resizing doesnt cause collision issues
        float deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20.0f)
            deltaTime = 1.0f / 20.0f;

        sf::Event event;
        while (window.pollEvent(event))
        {
            world.handleEvent(event, window, uiView);
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    resizeView(window, camera);
                    resizeView(window, uiView);
                    break;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        gameState.togglePause();
                    }
                    break;
                default:
                    break;
            }
        }
        window.clear(sf::Color(135, 206, 235));
        world.update(window, deltaTime, camera, uiView);
        // clamp view width to map size
        // todo: fix right world bounds due to player width offset
        sf::Vector2f camera_bounds(std::clamp(world.getPlayerPosition().x, VIEW_WIDTH * 0.5f, MAP_WIDTH * TILE_SIZE - VIEW_WIDTH * 0.5f ), world.getPlayerPosition().y); 
        camera.setCenter(camera_bounds);
        world.draw(window, camera, uiView);
        window.display();
    }
}