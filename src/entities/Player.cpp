#include "entities/Player.h"
#include "config/PhysicsConstants.h"

// initialize player
// use reference to texture to signify that the player owns that sprite texture and directly depends on being valid and uses it
// construct the animation before the constructor body executes
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
    body.setTexture(texture);
    body.setTextureRect(animation.uvRect);
    // set the players origin
    sf::FloatRect bounds = body.getLocalBounds();
    body.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    body.setScale(1.5f, 1.5f);

    // initial positon in the world
    body.setPosition(300.0f, -100.0f);

    // initialize the hitbox for the player
    hitbox.setSize(sf::Vector2f(bounds.width, bounds.height));
    hitbox.setOrigin(hitbox.getSize() / 2.0f);
    hitbox.setScale(0.75f, 0.75f);
    hitbox.setPosition(body.getPosition());
    hitbox.setFillColor(sf::Color::Red);
}

Player::~Player()
{

}

// draw the body of the player on the window
void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
    //window.draw(hitbox);
}

// update the players state and position based on user input
void Player::Update(float deltaTime)
{
    // keep track of old player state
    static PlayerState previousPlayerState = playerState;

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

    // update animation and move body depending on state and direction
    animation.Update(playerState, deltaTime, NUM_FRAMES[playerState], faceLeft);
    body.setTextureRect(animation.uvRect);
    // move the sprite by an "offset" defined in the vector2f movement
    body.move(velocity * deltaTime);
    hitbox.setPosition(body.getPosition() + hitboxOffset);
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
    body.setPosition(hitbox.getPosition() - hitboxOffset);
}