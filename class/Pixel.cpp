#include "Pixel.hpp"

Pixel::Pixel()
:
amount(0.0),
Wall(false),
neighborCount(0),
direction(0.0)
{}

Pixel::~Pixel() {}


double Pixel::GetAmount() { return amount; }
void Pixel::SetAmount(double amount) { this->amount = amount; }

sf::Color Pixel::GetColor() { return color; }
void Pixel::SetColor(sf::Color color) { this->color = color; }

std::vector<double> Pixel::Expand() { return expandAmounts; }

void Pixel::ExpandCalculate() {
    //Ignore direction for now
    int n = neighborCount;
    double distributedAmount = amount / (n + 1);
    expandAmounts.clear();
    for (int i = 0; i < 9; i++) {
        expandAmounts.push_back(distributedAmount);
    }
}


bool Pixel::isWall() { return Wall; }
