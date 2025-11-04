#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Animation.h"

int main()
{
    // initialize window object, viewport size x-800 y-600, window name terraria clone
    sf::RenderWindow window(sf::VideoMode(800, 600), "Terraria CLONE", sf::Style::Close | sf::Style::Resize);
    // initialize the player as a rectangle shape
    sf::RectangleShape player(sf::Vector2f(50,75));
    // set the players initial position in the window
    player.setPosition(sf::Vector2f(200.0f, 200.f));
    // initialize a player texture object and load the file we want to use as the texture
    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/player.png");
    // set the texture for the player to the playerTexture reference
    player.setTexture(&playerTexture);

    // initialize an animation object for the player
    // spritesheet orgainzed in on row for all states, 19 frames, walk, jump, hit, etc...
    Animation animation(&playerTexture, sf::Vector2u(13, 4), 0.1f);

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
        animation.Update(0, deltaTime);
        player.setTextureRect(animation.uvRect);

        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}