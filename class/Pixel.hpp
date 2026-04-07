#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
class Pixel
{
public:
    Pixel();
    ~Pixel();

    double GetAmount() const  { return amount; }
    void SetAmount(double amount) { this->amount = amount; }

    sf::Color GetColor() const { return color; }
    void SetColor(sf::Color color, double transparency) { this->color = sf::Color(color.r, color.g, color.b, transparency); }

    std::vector<double> Expand() const { return expandAmounts; }

    bool isWall() const { return Wall; }

    void ExpandCalculate();
private:
    double amount;
    double direction;
    sf::Color color;
    std::vector<double> expandAmounts;
    int neighborCount;
    bool Wall;
};
