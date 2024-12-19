#pragma once

#include "Rectangle.hpp"

#include <iostream>

void print(const Rectangle& rect)
{
    std::cout << "printing rectangle with corners:" << std::endl;
    for(const auto& corner: rect.getCorners())
    {
        std::cout << "\t" << corner;
    }
    std::cout << std::endl;
}
