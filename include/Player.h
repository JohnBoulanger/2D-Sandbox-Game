// PlayerState.h
#pragma once

enum PlayerState {
    WALK = 0,
    JUMP,
    SWING,
    IDLE,
    NUM_STATES
};

// frame counts
constexpr int NUM_WALK_FRAMES = 13;
constexpr int NUM_JUMP_FRAMES = 1;
constexpr int NUM_SWING_FRAMES = 4;
constexpr int NUM_IDLE_FRAMES = 1;


constexpr int NUM_FRAMES[NUM_STATES] = {
    NUM_WALK_FRAMES,
    NUM_JUMP_FRAMES,
    NUM_SWING_FRAMES,
    NUM_IDLE_FRAMES
};
