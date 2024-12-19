#pragma once

#include "Point.hpp"

class FancyRectangle
{
public:
    FancyRectangle(Point p, int w, int h):middle(p),width(w),height(h)
    {}

    void update()
    {
        middle = middle +  Point{.x = 1, .y = 1};
    }

    Point middle;
    int width, height;
};
