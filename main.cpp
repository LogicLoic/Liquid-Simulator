#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Window", sf::State::Windowed);
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                cout << "Window closed event received." << std::endl;
            }
        }
        window.clear(sf::Color::Black);
        window.display();
    }
    return 0;
}
