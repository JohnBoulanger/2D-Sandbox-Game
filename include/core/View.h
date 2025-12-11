#pragma once
#include <SFML/Graphics.hpp>

static const float VIEW_HEIGHT = 300.0f;
static const float VIEW_WIDTH  = VIEW_HEIGHT * (4.0f / 3.0f);

void resizeView(const sf::RenderWindow& window, sf::View& view);
