#include "Panel.hpp"

Panel::Panel() {}
Panel::~Panel() {}

void Panel::UpdateLayout(sf::RenderWindow& window) {
    auto size = window.getSize();

    width = size.x * 0.2f;
    xOffset = size.x - width;

    background.setSize(sf::Vector2f(width, size.y));
    background.setPosition(sf::Vector2f(xOffset, 0));
    background.setFillColor(sf::Color(50, 50, 50));
}

void Panel::Draw(sf::RenderWindow& window) {
    window.draw(background);
}

bool Panel::IsInside(int x) const {
    return x >= xOffset;
}