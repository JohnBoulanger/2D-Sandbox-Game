#include "View.h"

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);
    float targetRatio = VIEW_WIDTH / VIEW_HEIGHT;

    if (aspectRatio >= targetRatio)
    {
        // window wider than target: pillarbox
        float newWidth = VIEW_HEIGHT * aspectRatio;
        view.setSize(newWidth, VIEW_HEIGHT);
    }
    else
    {
        // window taller than target: letterbox
        float newHeight = VIEW_WIDTH / aspectRatio;
        view.setSize(VIEW_WIDTH, newHeight);
    }
}