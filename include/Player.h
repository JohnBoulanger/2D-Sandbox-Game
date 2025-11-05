#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "PlayerState.h"

class Player
{
public:
    Player(PlayerState playerState, sf::Texture& texture, sf::Vector2u imageCount, float switchTime, float speed);
    ~Player();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);

private:
    PlayerState playerState;
    sf::Sprite body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceLeft;
};