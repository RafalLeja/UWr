#pragma once

#include "Recipe.hpp"
#include "Ingredients.hpp"

#include <vector>

enum SearchRecipeMode {withLeftovers, withBuying, useAll};

struct Cookbook
{
    void addRecipe(Recipe&& r)
    {
        recipes.push_back(r);
    }

    std::vector<Recipe> findRecipes(const Ingredients& available, SearchRecipeMode mode) const
    {
        std::vector<Recipe> result;
        for(const auto& recipe: recipes)
        {
            if(mode == SearchRecipeMode::useAll and useAll(available, recipe))
                result.push_back(recipe);
            if(mode == SearchRecipeMode::withBuying and withBuying(available, recipe))
                result.push_back(recipe);
            if(mode == SearchRecipeMode::withLeftovers and withLeftovers(available, recipe))
                result.push_back(recipe);
        }
        return result;
    }

private:
    bool useAll(const Ingredients& available, const Recipe& recipe) const
    {
        return recipe.ingredients == available;
    }

    bool withBuying(const Ingredients& available, const Recipe& recipe) const
    {
        return available.isSubsetOf(recipe.ingredients);
    }

    bool withLeftovers(const Ingredients& available, const Recipe& recipe) const
    {
        return recipe.ingredients.isSubsetOf(available);
    }

    std::vector<Recipe> recipes;
};
