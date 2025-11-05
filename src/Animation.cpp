#include "../include/Animation.h"

// Animation constructor
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    // initialize imageCount and switchTime using this-> as constructor parameters have the same name
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    // starting animation frame
    currentImage.x = 0;

    // calculate the width of the sprite based on the dimensions of the sprite sheet
    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

// Animation destructor
Animation::~Animation()
{

}

// Update the animation object every fram
void Animation::Update(int row, float deltaTime, int numFrames, bool faceLeft) 
{
    // set spritesheet row and time passed since the most recent frame
    currentImage.y = row;
    totalTime += deltaTime;

    // if the time passed since last frame is greater than the animation speed, change frames
    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= numFrames)
        {
            currentImage.x = 0;
        }
    }
    
    // set the coordiantes in pixels of the top left portion of the sprite we will use in the spritesheet
    // if faceLeft true, face the user sprite to the left
    if (faceLeft)
    {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    // otherwise, flip the sprite by multiplying the width by -1
    else
    {
        uvRect.left = (currentImage.x + 1) * -uvRect.width;
        uvRect.width = -abs(uvRect.width);
    }
    uvRect.top = currentImage.y * uvRect.height;
}

void Animation::Reset()
{
    currentImage.x = 0;
    totalTime = 0;
}