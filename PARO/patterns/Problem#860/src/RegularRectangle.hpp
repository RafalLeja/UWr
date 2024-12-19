#pragma once
#include "Point.hpp"
#include "Rectangle.hpp"

#include <vector>

class RegularRectangle: public Rectangle
{
public:
    RegularRectangle(Point lu, Point rd) : leftUpCorner(lu), rightDownCorner(rd){}
    std::vector<Point> getCorners() const override
    {
        return {leftUpCorner, rightDownCorner};
    }
private:
    Point leftUpCorner, rightDownCorner;
};
