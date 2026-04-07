#pragma once

#include <vector>
#include "Pixel.hpp"
#include "Unit.hpp"
class Map
{
public:
    Map(int width, int height);
    ~Map();
    int GetWidth() { return width; }
    int GetHeight() { return height; }
    void Update();
    double GetTotalAmount();
    std::vector<std::vector<Pixel> >& GetPixels() { return pixels; }

private:
    int width;
    int height;
    std::vector<std::vector<Pixel> > pixels;
    std::vector<std::vector<Pixel>> pixels_next;
    std::vector<Unit> units;
};
