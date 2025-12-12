#pragma once

#include <string>
#include "Unit.hpp"

class Emitter : public Unit
{
public:
    Emitter();
    ~Emitter();
    void Emit();
    bool GetAdditional();

private:
    double amount;
    double interval;
    bool additional;
    std::string color;
};
