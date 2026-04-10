#pragma once
#include <SFML/Graphics.hpp>

class Panel {
public:
    Panel();
    ~Panel();

    void UpdateLayout(sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    
    bool IsInside(int x) const;

private:
    sf::RectangleShape background;

    float width;
    float xOffset;
};