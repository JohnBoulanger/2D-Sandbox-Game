#include "entities/Player.h"
#include "config/PhysicsConstants.h"
#include <config/TileConstants.h>
#include <config/MapConstants.h>

// initialize player
// use reference to texture to signify that the player owns that sprite texture and directly depends on being valid and uses it
// construct the animation before the constructor playerBody executes
Player::Player(PlayerState playerState, sf::Texture& texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
    animation(&texture, imageCount, switchTime),
    collider(hitbox)
{
    this->speed = speed;
    this->jumpHeight = jumpHeight;
    row = 0;
    faceLeft = true;
    playerState = IDLE;

    // set the texture for the player to the playerTexture reference
    playerBody.setTexture(texture);
    playerBody.setTextureRect(animation.uvRect);
    // set the players origin
    sf::FloatRect bounds = playerBody.getLocalBounds();
    playerBody.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    playerBody.setScale(1.5f, 1.5f);

    // initial positon in the world
    playerBody.setPosition(MAP_WIDTH * TILE_SIZE * 0.5, (GROUND_TO_TOP - 10) * TILE_SIZE);

    // initialize the hitbox for the player
    hitbox.setSize(sf::Vector2f(bounds.width, bounds.height));
    hitbox.setOrigin(hitbox.getSize() / 2.0f);
    hitbox.setPosition(playerBody.getPosition());
    hitbox.setFillColor(sf::Color::Red);
}

Player::~Player()
{

}

// draw the playerBody of the player on the window
void Player::Draw(sf::RenderWindow& window)
{
    window.draw(playerBody);
    // window.draw(hitbox);
}

// update the players state and position based on user input
void Player::Update(float deltaTime)
{
    // update movement and player state
    UpdateMovement(deltaTime);
    UpdateState();

    // update animation and move playerBody depending on state and direction
    animation.Update(playerState, deltaTime, NUM_FRAMES[playerState], faceLeft);
    playerBody.setTextureRect(animation.uvRect);
}

void Player::OnCollision(sf::Vector2f direction)
{
    // colliding with something to the left
    if (direction.x < 0.0f)
    {
        velocity.x = 0;
    }
    // right
    else if (direction.x > 0.0f)
    {
        velocity.x = 0;
    }
    // below
    if (direction.y < 0.0f)
    {
        velocity.y = 0;
        canJump = true;
    }
    // above
    else if (direction.y > 0.0f)
    {
        velocity.y = 0;
    }
    // collision moves the hitbox itself, not the player
    // so snap the player back to hits hitbox after the collision is handled
    playerBody.setPosition(hitbox.getPosition() - hitboxOffset);
}

void Player::UpdateMovement(float deltaTime)
{
    // initial x velocity to 0 if nothing pressed
    velocity.x = 0.0f;

    // get user input and update movement speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity.x += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
    {
        canJump = false;
        velocity.y = -sqrtf(GRAVITY * jumpHeight);
    }

    velocity.y += GRAVITY * deltaTime;
    // clamp max velocity in the y direction
    velocity.y = std::clamp(velocity.y, -MAX_Y, MAX_Y);
    // move the sprite by an "offset" defined in the vector2f movement
    playerBody.move(velocity * deltaTime);
    hitbox.setPosition(playerBody.getPosition() + hitboxOffset);
}

void Player::UpdateState()
{
    // keep track of old player state
    static PlayerState previousPlayerState = playerState;

    // determine state based on player movement which determines what sprite to render
    if (canJump && velocity.x == 0.0f)
        playerState = IDLE;
    if (abs(velocity.x) > 0.0f)
    {
        playerState = WALK;
        faceLeft = (velocity.x < 0.0f);
    }
    if (!canJump)
    {
        playerState = JUMP;
    } 

    // if the player has changed states, use sprite frame 0 of the new state by calling reset
    if (previousPlayerState != playerState)
    {
        animation.Reset();
        previousPlayerState = playerState;
    }
}