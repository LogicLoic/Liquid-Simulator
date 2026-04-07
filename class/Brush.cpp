#include "Brush.hpp"

Brush::Brush() :
amount(1000.0), color(sf::Color(0, 255, 255, 255)), type(BrushType::Liquid) 
{}

Brush::~Brush() {}

void Brush::RefreshInfos(double amount, sf::Color color, BrushType type) {
    this->amount = amount;
    this->color = color;
    this->type = type;
}