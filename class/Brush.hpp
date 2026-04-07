#pragma once

#include <SFML/Graphics.hpp>

enum class BrushType {
    Liquid,
    Wall,
    Erase, 
    Emitter
};

class Brush
{
public:
    Brush();
    ~Brush();
    double GetAmount() const { return amount; }
    sf::Color GetColor() const { return color; }
    BrushType GetType() const { return type; }
    void RefreshInfos(double amount, sf::Color color, BrushType type);
private:
    double amount;
    sf::Color color;
    BrushType type;
};
