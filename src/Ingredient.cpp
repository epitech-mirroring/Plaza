/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Ingredient.hpp"

std::ostream &operator<<(std::ostream &os, const Ingredient &ingredient) {
    switch (ingredient) {
        case Ingredient::Dough:
            os << "Dough";
            break;
        case Ingredient::Tomato:
            os << "Tomato";
            break;
        case Ingredient::Gruyere:
            os << "Gruyere";
            break;
        case Ingredient::Ham:
            os << "Ham";
            break;
        case Ingredient::Mushrooms:
            os << "Mushrooms";
            break;
        case Ingredient::Steak:
            os << "Steak";
            break;
        case Ingredient::Eggplant:
            os << "Eggplant";
            break;
        case Ingredient::GoatCheese:
            os << "Goat cheese";
            break;
        case Ingredient::ChiefLove:
            os << "Chief's love";
            break;
    }
    return os;
}
