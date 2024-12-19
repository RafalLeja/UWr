#pragma once
#include "Rectangle.hpp"
#include "FancyRectangle.hpp"
#include "RegularRectangle.hpp"

class FancyToRegular: public Rectangle
{
public:
    FancyToRegular(FancyRectangle *fr){
        rect = fr;
    }
    
    std::vector<Point> getCorners() const override
    {
        Point lu;
        lu.x = rect->middle.x + (rect->height/2);
        lu.y = rect->middle.y + (rect->width/2);
        Point rd;
        rd.x = rect->middle.x - (rect->height/2);
        rd.y = rect->middle.y - (rect->width/2);

        return std::vector<Point>{rd, lu};
    }

private:
    FancyRectangle *rect;
};

