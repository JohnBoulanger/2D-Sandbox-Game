#include "entities/Collider.h"

Collider::Collider(sf::RectangleShape& body) 
: body(body) 
{

}

Collider::~Collider() 
{

}

bool Collider::checkCollision(Collider& other, sf::Vector2f& direction, float pushFactor)
{
    // "other" is player in this case
    sf::Vector2f otherPosition = other.getPosition();
    sf::Vector2f otherHalfSize = other.getHalfSize();
    sf::Vector2f thisPosition = getPosition();
    sf::Vector2f thisHalfSize = getHalfSize();

    // find distance between the two objects
    float dx = otherPosition.x - thisPosition.x;
    float dy = otherPosition.y - thisPosition.y;

    // if negative, the two rectangles are intersecting
    float intersectX = abs(dx) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(dy) - (otherHalfSize.y + thisHalfSize.y);

    // check for a collision
    if (intersectX < 0.0f && intersectY < 0.0f)
    {
        // clamp pushFactor between 0 an 1
        pushFactor = std::clamp(pushFactor, 0.0f, 1.0f);

        if (intersectX > intersectY)
        {
            // other object is right of this object
            // move colliding objects in opposite directions in the x-axis (intersect X is currently negative already)
            if (dx > 0.0f)
            {
                // colliding with something to the right of us
                move(intersectX * (1.0f - pushFactor), 0.0f);
                other.move(-intersectX * pushFactor, 0.0f);

                direction.x = 1.0f;
                direction.y = 0.0f;
            }
            else 
            {
                // colliding with something to the left of us
                move(-intersectX * (1.0f - pushFactor), 0.0f);
                other.move(intersectX * pushFactor, 0.0f);

                direction.x = -1.0f;
                direction.y = 0.0f;
            }
        }
        else
        {
            if (dy > 0.0f)
            {
                // colliding with something underneath us
                move(0.0f, intersectY * (1.0f - pushFactor));
                other.move(0.0f, -intersectY * pushFactor);

                direction.x = 0.0f;
                direction.y = 1.0f;
            }
            else 
            {
                // colliding with something above us
                move(0.0f, -intersectY * (1.0f - pushFactor));
                other.move(0.0f, intersectY * pushFactor);

                direction.x = 0.0f;
                direction.y = -1.0f;
            }
        }

        return true;
    }

    return false;
}
