#pragma once

#include <string>
#include "Unit.hpp"
#include <SFML/Graphics.hpp>
class Emitter : public Unit
{
public:
    Emitter();
    ~Emitter();
    void Emit();
    bool GetAdditional() { return additional; }

private:
    double amount;
    double interval;
    bool additional;
    sf::Color color;
};
