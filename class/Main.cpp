#include "Main.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

Main::Main(int width, int height)
    : map(width, height)
    {
        units = std::vector<Unit>();
        
        sf::RenderWindow window(sf::VideoMode({width, height}), "SFML Window", sf::State::Windowed);
        while (window.isOpen()) {
            while (auto event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    cout << "Window closed event received." << endl;
                }
            }
            window.clear(sf::Color::Black);
            window.display();
        }
}

Main::~Main() {}
//void Main::Mouse(Event event) {}
//void Main::LClick(Event event) {}
void Main::NextFrame() {}
