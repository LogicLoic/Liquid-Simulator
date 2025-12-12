#pragma once

#include <vector>

class Map
{
public:
    Map();
    ~Map();
    void Map(int width, int height);
    void ~Map();
    void Update();
    double GetTotalAmount();

private:
    int width;
    int height;
    std::vector<std::vector<Pixel>> pixels;
};
