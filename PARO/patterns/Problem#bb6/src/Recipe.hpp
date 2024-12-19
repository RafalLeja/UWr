#pragma once

#include "Ingredients.hpp"

#include <string>

struct Recipe
{
    std::string name;
    std::string instructions;
    Ingredients ingredients;

    bool operator==(const Recipe& other) const
    {
        return name == other.name and
               instructions == other.instructions and
               ingredients == other.ingredients;
    }
};