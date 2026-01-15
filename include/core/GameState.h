#pragma once

class GameState {
public:
    bool isPaused() const { return paused; }
    void togglePause() { paused = !paused; }
    bool isInStartMenu() const { return inStartMenu; }
    void toggleStartMenu() { inStartMenu = !inStartMenu; }

private:
    bool paused = false;
    bool inStartMenu = true;
};
