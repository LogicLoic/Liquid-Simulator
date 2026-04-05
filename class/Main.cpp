#include "Main.hpp"
#include <iostream>

Main::Main(unsigned int width, unsigned int height)
    : map(width, height)
    {
        sf::RenderWindow window(sf::VideoMode({width, height}), "SFML Window", sf::State::Windowed);
        while (window.isOpen()) {
            while (auto event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    std::cout << "Window closed event received." << std::endl;
                }
            }
            window.clear(sf::Color::Black);

            Plot(window, 100, 100, sf::Color::Red);

            window.display();
        }
}

Main::~Main() {}

void Main::NextFrame() {
    for (auto line : map.GetPixels()) {
        for (auto pixel : line) {
            std::cout << pixel.GetAmount() << " ";
        }
        std::cout << std::endl;
    }
}

void Main::Plot(sf::RenderWindow& window, int x, int y, sf::Color color) {
    sf::VertexArray point(sf::PrimitiveType::Points, 1);
    point[0].position = sf::Vector2f(x, y);
    point[0].color = color;

    window.draw(point);
}

//void Main::Mouse(Event event) {}
//void Main::LClick(Event event) {}
