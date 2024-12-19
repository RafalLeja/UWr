#pragma once

#include "Recipe.hpp"
#include "RecipeFilter.hpp"

struct UseAll : RecipeFilter
{
    UseAll(const Ingredients& i) : RecipeFilter(i)
    {
    }
};
