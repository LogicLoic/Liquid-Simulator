#pragma once

#include <vector>
#include "Map.hpp"
#include "Unit.hpp"

class Main
{
public:
    Main(unsigned int width, unsigned int height);
    ~Main();
    //void Mouse(Event event);
    //void LClick(Event event);
    void NextFrame();

private:
    Map map;
    std::vector<Unit> units;
};
