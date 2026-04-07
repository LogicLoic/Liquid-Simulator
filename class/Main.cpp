#include "Main.hpp"
#include <iostream>

Main::Main(unsigned int width, unsigned int height)
    : map(width, height)
    {
        sf::RenderWindow window(sf::VideoMode({width, height}), "Liquid Simulator", sf::State::Windowed);
        Loop(window, width, height);
}

Main::~Main() {}

void Main::NextFrame(sf::RenderWindow& window) {
    sf::VertexArray vertices(sf::PrimitiveType::Points, map.GetHeight() * map.GetWidth());
    const auto& pixels = map.GetPixels();
    size_t idx = 0;
    double transparency;

    for (size_t y = 0; y < pixels.size(); ++y) {
        for (size_t x = 0; x < pixels[y].size(); ++x) {
            vertices[idx].position = sf::Vector2f(x, y);
            vertices[idx].color = pixels[y][x].GetColor();
            idx++;
        }
    }

    window.draw(vertices);
}


void Main::Event(sf::RenderWindow&window, bool& isDragging) {
    while (auto event = window.pollEvent()) {

        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (event->is<sf::Event::MouseButtonPressed>()) {
            auto e = event->getIf<sf::Event::MouseButtonPressed>();
            if (e && e->button == sf::Mouse::Button::Left) {
                isDragging = true;
            }
        }

        if (event->is<sf::Event::MouseButtonReleased>()) {
            auto e = event->getIf<sf::Event::MouseButtonReleased>();
            if (e && e->button == sf::Mouse::Button::Left) {
                isDragging = false;
            }
        }
    }
}

void Main::Loop(sf::RenderWindow& window, unsigned int width, unsigned int height) {
    bool isDragging = false;

    sf::Clock clock;
    int frameCount = 0;
    float timer = 0.0f;

    while (window.isOpen()) {
        Event(window, isDragging);

        float deltaTime = clock.restart().asSeconds();
        timer += deltaTime;
        frameCount++;

        window.clear(sf::Color::Black);

        if (timer >= 1.0f) {
            int fps = frameCount;
            window.setTitle("Liquid Simulator - FPS: " + std::to_string(fps));

            frameCount = 0;
            timer = 0.0f;
        }

        if (isDragging) {
            sf::Vector2i pos = sf::Mouse::getPosition(window);

            int x = pos.x;
            int y = pos.y;

            if (x >= 0 && x < width && y >= 0 && y < height) {
                map.GetPixels()[y][x].SetAmount(brush.GetAmount());
                double transparency = (brush.GetAmount() / maxAmount) * 255.0;
                if (transparency > 255.0) transparency = 255.0;
                map.GetPixels()[y][x].SetColor(brush.GetColor(), transparency);
            }
        }
        map.Update();
        NextFrame(window);
        window.display();
    }
}