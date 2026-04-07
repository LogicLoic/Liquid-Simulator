#include "Map.hpp"

Map::Map(int width, int height)
:
width(width),
height(height)
{
    pixels.resize(height);
    pixels_next.resize(height);
    for (int i = 0; i < height; i++) {
        pixels[i].resize(width);
        pixels_next[i].resize(width);
        for (int j = 0; j < width; j++) {
            pixels[i][j] = Pixel();
            pixels_next[i][j] = Pixel();
        }
    }
}


Map::~Map() {}


void Map::Update() {
    const int width = this->width;
    const int height = this->height;

    double transparency;

    const int dx[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    const int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};


    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            pixels_next[y][x].SetAmount(0.0f);
        }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float value = pixels[y][x].GetAmount();
            sf::Color sourceColor = pixels[y][x].GetColor();

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

                float targetAmount = pixels_next[ny][nx].GetAmount();
                sf::Color targetColor = pixels_next[ny][nx].GetColor();

                if (targetColor != sourceColor) {
                    targetAmount -= amount;
                    if (targetAmount < 0.0f) {
                        targetAmount = -targetAmount;
                        targetColor = sourceColor;
                    }
                } else {
                    targetAmount += amount;
                }

                pixels_next[ny][nx].SetAmount(targetAmount);
                transparency = (pixels_next[ny][nx].GetAmount() / 1000.0) * 255.0;
                if (transparency > 255.0) transparency = 255.0;
                pixels_next[ny][nx].SetColor(targetColor, transparency);

                totalDistributed += amount;
            }

            float remaining = value - totalDistributed;
            if (remaining < 0.0f) remaining = 0.0f;

            float selfAmount = pixels_next[y][x].GetAmount() + remaining;
            pixels_next[y][x].SetAmount(selfAmount);
            transparency = (pixels_next[y][x].GetAmount() / 1000.0) * 255.0;
            if (transparency > 255.0) transparency = 255.0;
            pixels_next[y][x].SetColor(sourceColor, transparency);
        }
    }

    pixels.swap(pixels_next);
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
