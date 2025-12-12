#pragma once

#include <vector>

class Unit
{
public:
    Unit();
    virtual ~Unit();
    void Unit();
    void ~Unit();
    std::vector<int> GetCoords();

private:
    int x;
    int y;
};
