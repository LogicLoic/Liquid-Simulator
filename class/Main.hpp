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
    void NextFrame(sf::RenderWindow& window);
    void Event(sf::RenderWindow&window, bool& isDragging);
    void Loop(sf::RenderWindow& window, unsigned int width, unsigned int height);
private:
    Map map;
    std::vector<Unit> units;
};
