// PlayerState.h
#pragma once

// define player states
enum PlayerState {
    WALK = 0,
    JUMP,
    SWING,
    IDLE,
    NUM_STATES
};

// frames needed for each animation
constexpr int NUM_WALK_FRAMES = 13;
constexpr int NUM_JUMP_FRAMES = 1;
constexpr int NUM_SWING_FRAMES = 4;
constexpr int NUM_IDLE_FRAMES = 1;

// store number of frames for the animation based on players state
constexpr int NUM_FRAMES[NUM_STATES] = {
    NUM_WALK_FRAMES,
    NUM_JUMP_FRAMES,
    NUM_SWING_FRAMES,
    NUM_IDLE_FRAMES
};
