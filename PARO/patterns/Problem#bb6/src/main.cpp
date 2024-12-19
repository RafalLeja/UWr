#include "Cookbook.hpp"

#include <iostream>

void printRecipes(const Cookbook& cookbook, const Ingredients& ingredients, SearchRecipeMode mode)
{
    std::cout << "with " << ingredients << " you can do:" << std::endl;
    for (const auto& recipe : cookbook.findRecipes(ingredients, mode))
        std::cout << "\t" << recipe.name << ": " << recipe.ingredients << std::endl;
}

int main()
{
    Cookbook cookbook;
    cookbook.addRecipe(
        {.name = "butter on bread", .instructions = "spread butter on bread", .ingredients = {"bread", "butter"}});
    cookbook.addRecipe(
        {.name = "bread with jelly",
         .instructions = "spread butter on bread, add jelly",
         .ingredients = {"bread", "butter", "jelly"}});

    printRecipes(cookbook, {"bread", "butter"}, SearchRecipeMode::useAll);
    printRecipes(cookbook, {"bread", "jelly"}, SearchRecipeMode::withBuying);
    printRecipes(cookbook, {"bread", "butter", "jelly"}, SearchRecipeMode::withLeftovers);
    printRecipes(cookbook, {"bread"}, SearchRecipeMode::withBuying);
}
