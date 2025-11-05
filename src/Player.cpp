#include "Player.h"

Player::Player(PlayerState playerState, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed) :
    animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    row = 0;
    faceLeft = true;
    playerState = IDLE;

    // initialize the player as a rectangle shape
    body.setSize(sf::Vector2f(50,75));
    // set the players initial position in the window
    body.setPosition(sf::Vector2f(200.0f, 200.f));
    // set the texture for the player to the playerTexture reference
    body.setTexture(texture);
}

Player::~Player()
{

}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

void Player::Update(float deltaTime)
{
    static PlayerState previousPlayerState = playerState;
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += speed * deltaTime;

    // determine state
    if (movement.x == 0.0f)
        playerState = IDLE;
    else {
        playerState = WALK;
        faceLeft = (movement.x < 0.0f);
    }

    // now detect transition 
    if (previousPlayerState != playerState)
    {
        animation.Reset();
        previousPlayerState = playerState;
    }

    // update animation and move body
    animation.Update(playerState, deltaTime, NUM_FRAMES[playerState], faceLeft);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
}
