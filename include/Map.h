#pragma once
#include <SFML/Graphics.hpp>

class Map
{
public:
    Map(int size);
    ~Map();

    void PrintMap();

private:
    std::vector<std::vector<int>> map;    
};