#pragma once
#include <string>
#include <vector>
#include <map>

struct WorldData {
    std::string name;
    std::string createdDate;
};

class WorldManager {
public:
    WorldManager();
    ~WorldManager();

    // Load world data from JSON file
    void loadWorlds();

    // Save world data to JSON file
    void saveWorlds();

    // Get world at slot (0-2)
    bool hasWorld(int slot) const;
    const WorldData& getWorld(int slot) const;

    // Create a new world at slot
    void createWorld(int slot, const std::string& name);

    // Delete world at slot
    void deleteWorld(int slot);

    // Get all worlds
    const std::map<int, WorldData>& getAllWorlds() const { return worlds; }

private:
    std::map<int, WorldData> worlds;
    const std::string WORLDS_FILE = "worlds/worlds.json";

    // JSON helper functions
    std::string generateJSON() const;
    void parseJSON(const std::string& jsonStr);
};
