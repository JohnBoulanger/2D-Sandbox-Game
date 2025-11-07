#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "PlayerState.h"
#include "Collider.h"

class Player
{
public:
    Player(PlayerState playerState, sf::Texture& texture, sf::Vector2u imageCount, float switchTime, float speed);
    ~Player();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);

    sf::Vector2f GetPosition() { return body.getPosition(); }
    Collider& GetCollider() { return collider; }

private:
    // player
    PlayerState playerState;
    sf::Sprite body;
    float speed;
    
    // player animation
    Animation animation;
    unsigned int row;
    bool faceLeft;

    // player hitbox
    sf::RectangleShape hitbox;
    Collider collider;
    sf::Vector2f hitboxOffset = {0.0f, 5.0f};
};