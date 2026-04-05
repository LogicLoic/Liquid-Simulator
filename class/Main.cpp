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

            map.GetPixels()[100][100].SetColor(sf::Color::Red);

            NextFrame(window);

            window.display();
        }
}

Main::~Main() {}

void Main::NextFrame(sf::RenderWindow& window) {
    sf::VertexArray vertices(sf::PrimitiveType::Points, map.GetHeight() * map.GetWidth());
    const auto& pixels = map.GetPixels();
    size_t idx = 0;

    for (size_t y = 0; y < pixels.size(); ++y) {
        for (size_t x = 0; x < pixels[y].size(); ++x) {
            vertices[idx].position = sf::Vector2f(x, y);
            vertices[idx].color = pixels[y][x].GetColor();
            idx++;
        }
    }

    window.draw(vertices);
}

//void Main::Mouse(Event event) {}
//void Main::LClick(Event event) {}
