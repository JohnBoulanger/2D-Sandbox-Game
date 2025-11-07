#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "PlayerState.h"
#include "Platform.h"
#include "PhysicsConstants.h"
#include "View.h"
#include "Map.h"

int main()
{
    // init window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Terraria CLONE", sf::Style::Close | sf::Style::Resize);

    // init player
    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/player.png");

    // init view
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

    // init player state and spritesheet
    PlayerState defaultPlayerState = IDLE;
    Player player(defaultPlayerState, playerTexture, sf::Vector2u(13, 4), 0.1f, SPEED, JUMP_HEIGHT);
    // create a platform for the player to stand on
    Platform platform1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(400.0f, 330.0f));
    // init map
    Map myMap(32);
    // print map
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            printf("%d", myMap.GetMap()[i][j]);
        }
        printf("\n");
    }


    float deltaTime = 0.0f;
    sf::Clock clock;
    
    // run the program as long as the window is open
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        if (deltaTime > 1.0f / 20.0f)
            deltaTime = 1.0f / 20.0f;

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
        sf::Vector2f direction;
        // if the player is colliding with something, determine which direction its coming from
        // then using that direction update the players velocity and jump state
        if (platform1.GetCollider().CheckCollision(player.GetCollider(), direction, 0.0f))
            player.OnCollision(direction);

        view.setCenter(player.GetPosition());

        window.clear();
        window.setView(view);
        player.Draw(window);
        platform1.Draw(window);
        window.display();

    }

    return 0;
}