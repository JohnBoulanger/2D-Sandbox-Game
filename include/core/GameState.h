#pragma once

class GameState {
public:
    bool isPaused() const { return paused; }
    void togglePause() { paused = !paused; }
    bool isInStartMenu() const { return inStartMenu; }
    void toggleStartMenu() { inStartMenu = !inStartMenu; }
    bool isInWorldSelectMenu() const { return inWorldSelectMenu; }
    void toggleWorldSelectMenu() { inWorldSelectMenu = !inWorldSelectMenu; }
    
    int getCreatingWorldSlot() const { return creatingWorldSlot; }
    void setCreatingWorldSlot(int slot) { creatingWorldSlot = slot; }

private:
    bool paused = false;
    bool inStartMenu = true;
    bool inWorldSelectMenu = false;
    int creatingWorldSlot = -1;
};
