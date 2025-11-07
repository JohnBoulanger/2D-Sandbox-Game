#pragma once
#include <SFML/Graphics.hpp>

class Map
{
public:
    Map(int size);
    ~Map();

    std::vector<std::vector<int>> GetMap() { return map; }

private:
    std::vector<std::vector<int>> map;    
};