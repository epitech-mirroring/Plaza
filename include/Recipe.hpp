/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <unordered_map>
#include <vector>
#include "Ingredient.hpp"
#include "Pizza.hpp"

class Recipe {
protected:
    Pizza::Type _type;
    std::vector<Ingredient> _ingredients;
    std::size_t _cookingTime;

public:
    Recipe(Pizza::Type type, std::vector<Ingredient> ingredients, std::size_t cookingTime);
    ~Recipe();

    [[nodiscard]] Pizza::Type getType() const;
    [[nodiscard]] std::vector<Ingredient> getIngredients() const;
    [[nodiscard]] std::size_t getCookingTime() const;
    void setType(Pizza::Type type);
    void setIngredients(std::vector<Ingredient> ingredients);
    void setCookingTime(std::size_t cookingTime);

    [[nodiscard]] std::size_t getCountOfIngredient(Ingredient ingredient) const;
};

extern const std::unordered_map<Pizza::Type, Recipe> RECIPIES;
