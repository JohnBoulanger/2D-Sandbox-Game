#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Animation.h"
#include "../include/Player.h"
#include "../include/PlayerState.h"


int main()
{
    // initialize window object, viewport size x-800 y-600, window name terraria clone
    sf::RenderWindow window(sf::VideoMode(800, 600), "Terraria CLONE", sf::Style::Close | sf::Style::Resize);
    // initialize a player texture object and load the file we want to use as the texture
    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/player.png");

    // initialize an animation object for the player
    // spritesheet orgainzed in on row for all states, 19 frames, walk, jump, hit, etc...
    PlayerState defaultPlayerState = IDLE;
    Player player(defaultPlayerState, &playerTexture, sf::Vector2u(13, 4), 0.1f, 100.0f);

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
                default:
                    break;

            }
        }
        player.Update(deltaTime);
        window.clear();
        player.Draw(window);
        window.display();
    }

    return 0;
}