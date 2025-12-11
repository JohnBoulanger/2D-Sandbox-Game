#include <SFML/Graphics.hpp>
#include "core/Animation.h"
#include "entities/PlayerState.h"
#include "entities/Collider.h"

class Player
{
public:
    Player(PlayerState playerState, sf::Texture& texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
    ~Player();

    void update(float deltaTime);
    void updateMovement(float deltaTime);
    void updateState();
    void draw(sf::RenderWindow& window);
    void onCollision(sf::Vector2f direction);

    // getters
    sf::Vector2f getPosition() { return playerBody.getPosition(); }
    Collider& getCollider() { return collider; }

private:
    // player
    PlayerState playerState;
    sf::Sprite playerBody;
    float speed;
    sf::Vector2f velocity;
    bool canJump;
    float jumpHeight;
    
    // player animation
    Animation animation;
    unsigned int row;
    bool faceLeft;

    // player hitbox
    sf::RectangleShape hitbox;
    Collider collider;
    sf::Vector2f hitboxOffset = {0.0f, 3.0f};
};