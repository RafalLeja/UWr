#pragma once

#include <iostream>

struct Point{
    int x,y;
    Point operator+(const Point other) const
    {
        return Point{.x = x + other.x, .y = y + other.y};
    }

    Point operator-(const Point other) const
    {
        return *this + Point{.x = -other.x, .y = -other.y};
    }
};


std::ostream& operator<<(std::ostream& out, const Point& p)
{
    return out << "(" << p.x << " " << p.y << ")";
}
