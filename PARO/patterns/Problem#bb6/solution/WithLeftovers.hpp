#pragma once

#include "Recipe.hpp"
#include "RecipeFilter.hpp"

struct WithLeftovers : RecipeFilter
{
    WithLeftovers(const Ingredients& i) : RecipeFilter(i)
    {
    }
};
