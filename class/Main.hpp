#pragma once

#include <vector>

class Main
{
public:
    Main();
    ~Main();
    void Main(int width, int height);
    void ~Main();
    void Mouse(Event event);
    void LClick(Event event);
    void NextFrame();

private:
    Map map;
    std::vector<Unit> units;
};
