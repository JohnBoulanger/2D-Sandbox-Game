#include <SFML/Graphics.hpp>
#include <entities/PlayerState.h>

// WINDOW
const std::string WINDOW_NAME = "Terraria!!";
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

// MAP
constexpr int MAP_WIDTH = 420;
constexpr int MAP_HEIGHT = 240;
constexpr int GROUND_TO_TOP = 128;

// PLAYER
constexpr float SPEED = 100.0f;
constexpr float GRAVITY = 981.0f;
constexpr float MAX_Y = 500.0f;
constexpr float JUMP_HEIGHT = 300.0f;
const std::string PLAYER_PATH = "textures/player.png";
constexpr PlayerState DEFAULT_PLAYER_STATE = IDLE;
constexpr unsigned int PLAYER_SPRITESHEET_WIDTH = 13;
constexpr unsigned int PLAYER_SPRITESHEET_HEIGHT = 4;
constexpr float PLAYER_ANIMATION_SPEED = 0.1f;


// WORLD

