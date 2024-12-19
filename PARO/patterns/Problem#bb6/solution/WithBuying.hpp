#pragma once

#include "Recipe.hpp"
#include "RecipeFilter.hpp"

struct WithBuying : RecipeFilter
{
    WithBuying(const Ingredients& i) : RecipeFilter(i)
    {
    }
};
