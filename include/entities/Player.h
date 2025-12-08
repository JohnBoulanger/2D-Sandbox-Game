#include <SFML/Graphics.hpp>
#include "core/Animation.h"
#include "entities/PlayerState.h"
#include "entities/Collider.h"

class Player
{
public:
    Player(PlayerState playerState, sf::Texture& texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
    ~Player();

    void Update(float deltaTime);
    void UpdateMovement(float deltaTime);
    void UpdateState();
    void Draw(sf::RenderWindow& window);
    void OnCollision(sf::Vector2f direction);

    // getters
    sf::Vector2f GetPosition() { return playerBody.getPosition(); }
    Collider& GetCollider() { return collider; }

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