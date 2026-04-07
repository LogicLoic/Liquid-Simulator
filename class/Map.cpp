#include "Map.hpp"

Map::Map(int width, int height)
:
width(width),
height(height)
{
    pixels.resize(height);
    for (int i = 0; i < height; i++) {
        pixels[i].resize(width);
        for (int j = 0; j < width; j++) {
            pixels[i][j] = Pixel();
        }
    }
}


Map::~Map() {}


void Map::Update() {
    const int width = this->width;
    const int height = this->height;

    auto& current = pixels;

    std::vector<std::vector<Pixel>> next(
        height, std::vector<Pixel>(width)
    );

    const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    const int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            float value = current[y][x].GetAmount();

            if (value <= 0.0f)
                continue;

            float totalDistributed = 0.0f;

            for (int i = 0; i < 8; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx < 0 || nx >= width || ny < 0 || ny >= height)
                    continue;

                float weight = (i < 4) ? 1.0f : 0.707f;

                float amount = value * 0.05f * weight;

                next[ny][nx].SetAmount(next[ny][nx].GetAmount() + amount);
                totalDistributed += amount;
            }

            next[y][x].SetAmount(next[y][x].GetAmount() + (value - totalDistributed));
            double transparency = (next[y][x].GetAmount() / 1000.0) * 255.0;
            if (transparency > 255.0) transparency = 255.0;
            next[y][x].SetColor(sf::Color::Red, transparency);
        }
    }

    pixels.swap(next);
}



double Map::GetTotalAmount() {
    double sum = 0.0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            sum += pixels[i][j].GetAmount();
        }
    }
    return sum;
}
