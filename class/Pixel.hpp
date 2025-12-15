#pragma once

#include <string>
#include <vector>

class Pixel
{
public:
    Pixel();
    ~Pixel();
    double GetAmount();
    void SetAmount(double amount);
    std::vector<double> Expand();
    void ExpandCalculate();
    bool isWall();

private:
    double amount;
    double direction;
    std::string color;
    std::vector<double> expandAmounts;
    int neighborCount;
    bool Wall;
};
