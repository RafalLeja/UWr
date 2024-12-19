#pragma once

#include "../src/Ingredients.hpp"

struct Recipe;

struct RecipeFilter
{
    RecipeFilter(const Ingredients& available) : available(available)
    {
    }
    virtual ~RecipeFilter() = default;

    virtual bool accepts(const Recipe& recipe) const = 0;

    const Ingredients available;
};
