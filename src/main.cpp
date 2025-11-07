#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "PlayerState.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 600.0f;
static const float VIEW_WIDTH  = VIEW_HEIGHT * (4.0f / 3.0f);

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
    float targetRatio = VIEW_WIDTH / VIEW_HEIGHT;

    if (aspectRatio >= targetRatio)
    {
        // window wider than target: pillarbox
        float newWidth = VIEW_HEIGHT * aspectRatio;
        view.setSize(newWidth, VIEW_HEIGHT);
    }
    else
    {
        // window taller than target: letterbox
        float newHeight = VIEW_WIDTH / aspectRatio;
        view.setSize(VIEW_WIDTH, newHeight);
    }
}


int main()
{
    // initialize window object, viewport size x-800 y-600, window name terraria clone
    sf::RenderWindow window(sf::VideoMode(800, 600), "Terraria CLONE", sf::Style::Close | sf::Style::Resize);
    // initialize a player texture object and load the file we want to use as the texture
    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/player.png");

    // create a view
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

    // initialize an animation object for the player
    // spritesheet orgainzed in on row for all states, 19 frames, walk, jump, hit, etc...
    PlayerState defaultPlayerState = IDLE;
    Player player(defaultPlayerState, playerTexture, sf::Vector2u(13, 4), 0.1f, 100.0f);

    // create a platform for the player to stand on
    Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(400.0f, 330.0f));

    float deltaTime = 0.0f;
    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                // if window closed
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    ResizeView(window, view);
                default:
                    break;

            }
        }
        // animate player and redraw
        player.Update(deltaTime);
        platform1.GetCollider().CheckCollision(player.GetCollider(), 0.0f);

        view.setCenter(player.GetPosition());

        window.clear();
        window.setView(view);
        player.Draw(window);
        platform1.Draw(window);
        window.display();

    }

    return 0;
}