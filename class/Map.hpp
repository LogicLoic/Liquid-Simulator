#pragma once

#include <vector>
#include "Pixel.hpp"
class Map
{
public:
    Map(int width, int height);
    ~Map();
    void Update();
    double GetTotalAmount();

private:
    int width;
    int height;
    std::vector<std::vector<Pixel>> pixels;
};
