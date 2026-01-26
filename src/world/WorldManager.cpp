#include "world/WorldManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <filesystem>

WorldManager::WorldManager()
{
    loadWorlds();
}

WorldManager::~WorldManager()
{
    saveWorlds();
}

void WorldManager::loadWorlds()
{
    std::ifstream file(WORLDS_FILE);
    if (!file.is_open()) {
        std::cout << "No worlds file found, starting fresh\n";
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    parseJSON(buffer.str());
}

void WorldManager::saveWorlds()
{
    // Ensure directory exists
    std::filesystem::create_directories("worlds");

    std::ofstream file(WORLDS_FILE);
    if (!file.is_open()) {
        std::cerr << "Failed to open worlds file for writing\n";
        return;
    }

    file << generateJSON();
    file.close();
}

bool WorldManager::hasWorld(int slot) const
{
    return worlds.find(slot) != worlds.end();
}

const WorldData& WorldManager::getWorld(int slot) const
{
    static WorldData empty = {"", ""};
    auto it = worlds.find(slot);
    if (it != worlds.end()) {
        return it->second;
    }
    return empty;
}

void WorldManager::createWorld(int slot, const std::string& name)
{
    // Get current date/time
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");

    worlds[slot] = {name, oss.str()};
    saveWorlds();
}

void WorldManager::deleteWorld(int slot)
{
    worlds.erase(slot);
    saveWorlds();
}

std::string WorldManager::generateJSON() const
{
    std::stringstream json;
    json << "{\n  \"worlds\": {\n";

    bool first = true;
    for (const auto& [slot, world] : worlds) {
        if (!first) json << ",\n";
        json << "    \"" << slot << "\": {\n"
             << "      \"name\": \"" << world.name << "\",\n"
             << "      \"created\": \"" << world.createdDate << "\"\n"
             << "    }";
        first = false;
    }

    json << "\n  }\n}";
    return json.str();
}

void WorldManager::parseJSON(const std::string& jsonStr)
{
    worlds.clear();

    // Simple JSON parser - look for slot objects
    size_t pos = 0;
    while ((pos = jsonStr.find("\"name\"", pos)) != std::string::npos) {
        // Find the slot number before this
        size_t slotStart = jsonStr.rfind("\"", pos - 2);
        slotStart = jsonStr.rfind("\"", slotStart - 1);
        size_t slotEnd = jsonStr.find("\"", slotStart + 1);
        std::string slotStr = jsonStr.substr(slotStart + 1, slotEnd - slotStart - 1);

        // Extract name
        size_t nameStart = jsonStr.find("\"", pos + 6) + 1;
        size_t nameEnd = jsonStr.find("\"", nameStart);
        std::string name = jsonStr.substr(nameStart, nameEnd - nameStart);

        // Extract created date
        size_t createdPos = jsonStr.find("\"created\"", pos);
        size_t dateStart = jsonStr.find("\"", createdPos + 9) + 1;
        size_t dateEnd = jsonStr.find("\"", dateStart);
        std::string created = jsonStr.substr(dateStart, dateEnd - dateStart);

        int slot = std::stoi(slotStr);
        worlds[slot] = {name, created};

        pos = nameEnd;
    }
}
