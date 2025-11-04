#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/Animation.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Terraria CLONE", sf::Style::Close | sf::Style::Resize);
    sf::RectangleShape player(sf::Vector2f(100,400.0/3.0));
    player.setPosition(sf::Vector2f(200.0f, 200.f));
    sf::Texture playerTexture;
    playerTexture.loadFromFile("textures/player.png");
    player.setTexture(&playerTexture);

    Animation animation(&playerTexture, sf::Vector2u(23, 4), 0.1f);

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
        animation.Update(1, deltaTime);
        player.setTextureRect(animation.uvRect);

        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}