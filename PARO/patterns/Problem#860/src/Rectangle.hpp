#pragma once
#include "Point.hpp"

#include <vector>

class Rectangle
{
public:
    virtual ~Rectangle() = default;

    virtual std::vector<Point> getCorners() const = 0;
};
