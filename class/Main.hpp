#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
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
    void Plot(sf::RenderWindow& window, int x, int y, std::string color);

private:
    Map map;
    std::vector<Unit> units;
};
