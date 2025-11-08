#include <SFML/Graphics.hpp>
#include "PlayerState.h"

const std::string PLAYER_PATH = "textures/player.png";
constexpr PlayerState DEFAULT_PLAYER_STATE = IDLE;
constexpr unsigned int PLAYER_SPRITESHEET_WIDTH = 13;
constexpr unsigned int PLAYER_SPRITESHEET_HEIGHT = 4;
constexpr float PLAYER_ANIMATION_SPEED = 0.1f;
