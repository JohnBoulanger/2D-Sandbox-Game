#include "FastNoiseLite.h"
#include "core/Game.h"
#include "config/GameConstants.h"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close | sf::Style::Resize),
      view({0.0f, 0.0f}, {VIEW_WIDTH, VIEW_HEIGHT})   
{

}


Game::~Game()
{

}

void Game::Run()
{
    // Create and configure FastNoise object
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    // Gather noise data
    std::vector<float> noiseData(128 * 128);
    int index = 0;

    for (int y = 0; y < 128; y++)
    {
        for (int x = 0; x < 128; x++)
        {
            noiseData[index++] = noise.GetNoise((float)x, (float)y);
        }
    }
    // core game loop
    while (window.isOpen())
    {
        // create maximum delta time so resizing doesnt cause collision issues
        float deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20.0f)
            deltaTime = 1.0f / 20.0f;

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
        window.clear();
        window.setView(view);
        world.Update(window, deltaTime);
        view.setCenter(world.GetPlayerPosition());
        world.Draw(window, view);
        window.display();
    }
}