/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Recipe.hpp"
#include <utility>

const std::unordered_map<Pizza::Type, Recipe> RECIPIES = {
    {Pizza::Type::Margarita, {Pizza::Type::Margarita, {Ingredient::Dough, Ingredient::Tomato, Ingredient::Gruyere}, 1}},
    {Pizza::Type::Regina, {Pizza::Type::Regina, {Ingredient::Dough, Ingredient::Tomato, Ingredient::Gruyere, Ingredient::Ham, Ingredient::Mushrooms}, 2}},
    {Pizza::Type::Americana, {Pizza::Type::Americana, {Ingredient::Dough, Ingredient::Tomato, Ingredient::Gruyere, Ingredient::Steak}, 2}},
    {Pizza::Type::Fantasia, {Pizza::Type::Fantasia, {Ingredient::Dough, Ingredient::Tomato, Ingredient::Eggplant, Ingredient::GoatCheese, Ingredient::ChiefLove}, 4}}
};

Recipe::Recipe(Pizza::Type type, std::vector<Ingredient> ingredients, std::size_t cookingTime) {
    _type = type;
    _ingredients = std::move(ingredients);
    _cookingTime = cookingTime;
}

Recipe::~Recipe() = default;

Pizza::Type Recipe::getType() const {
    return _type;
}

std::vector<Ingredient> Recipe::getIngredients() const {
    return _ingredients;
}

std::size_t Recipe::getCookingTime() const {
    return _cookingTime;
}

void Recipe::setType(Pizza::Type type) {
    _type = type;
}

void Recipe::setIngredients(std::vector<Ingredient> ingredients) {
    _ingredients = std::move(ingredients);
}

void Recipe::setCookingTime(std::size_t cookingTime) {
    _cookingTime = cookingTime;
}

std::size_t Recipe::getCountOfIngredient(Ingredient ingredient) const {
    std::size_t count = 0;

    for (const auto &ing : _ingredients) {
        if (ing == ingredient)
            count++;
    }
    return count;
}
