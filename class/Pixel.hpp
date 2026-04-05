#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
class Pixel
{
public:
    Pixel();
    ~Pixel();
    double GetAmount();
    void SetAmount(double amount);
    sf::Color GetColor();
    void SetColor(sf::Color color);
    std::vector<double> Expand();
    void ExpandCalculate();
    bool isWall();
private:
    double amount;
    double direction;
    sf::Color color;
    std::vector<double> expandAmounts;
    int neighborCount;
    bool Wall;
};
