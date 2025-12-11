#include "core/Animation.h"

// Animation constructor
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    // initialize imageCount and switchTime using this-> as constructor parameters have the same name
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    // starting animation frame
    currentImage.x = 0;

    // calculate the width of the sprite based on the dimensions of the sprite sheet and number of images
    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
}

// Animation destructor
Animation::~Animation()
{

}

// Update the animation object every frame
void Animation::update(int row, float deltaTime, int numFrames, bool faceLeft) 
{
    // set spritesheet row and time passed since the most recent frame
    currentImage.y = row;
    totalTime += deltaTime;

    // if the time passed since last frame is greater than the animation speed, change animation frames
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

// if the user switches state, use the first sprite in the animation and reset the total time for that frame back to 0
void Animation::reset()
{
    currentImage.x = 0;
    totalTime = 0;
}