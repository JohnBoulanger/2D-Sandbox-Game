#include "Player.h"

// initialize player
// use reference to texture to signify that the player owns that sprite texture and directly depends on being valid and uses it
// construct the animation before the constructor body executes
Player::Player(PlayerState playerState, sf::Texture& texture, sf::Vector2u imageCount, float switchTime, float speed) :
    animation(&texture, imageCount, switchTime)
{
    this->speed = speed;
    row = 0;
    faceLeft = true;
    playerState = IDLE;

    // initialize the player as a rectangle shape
    // set the players initial position in the window
    body.setPosition(sf::Vector2f(200.0f, 200.f));
    // set the texture for the player to the playerTexture reference
    body.setTexture(texture);
}

Player::~Player()
{

}

// draw the body of the player on the window
void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

// update the players state and position based on user input
void Player::Update(float deltaTime)
{
    // keep track of old player state
    static PlayerState previousPlayerState = playerState;
    // reset movement to 0 initially for each frame
    sf::Vector2f movement(0.0f, 0.0f);

    // get user input and update movement speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= speed * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += speed * deltaTime;

    // determine state based on player movement which determines what sprite to render
    if (movement.x == 0.0f)
        playerState = IDLE;
    else {
        playerState = WALK;
        faceLeft = (movement.x < 0.0f);
    }

    // if the player has changed states, use sprite frame 0 of the new state by calling reset
    if (previousPlayerState != playerState)
    {
        animation.Reset();
        previousPlayerState = playerState;
    }

    // update animation and move body depending on state and direction
    animation.Update(playerState, deltaTime, NUM_FRAMES[playerState], faceLeft);
    body.setTextureRect(animation.uvRect);
    // move the sprite by an "offset" defined in the vector2f movement
    body.move(movement);
}
