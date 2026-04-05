#pragma once

#include <vector>

class Unit
{
public:
    Unit();
    virtual ~Unit();
    std::vector<int> GetCoords() const { return {x, y}; }

private:
    int x;
    int y;
};
