/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <ostream>

enum Ingredient {
    Dough = 1,
    Tomato = 2,
    Gruyere = 3,
    Ham = 4,
    Mushrooms = 5,
    Steak = 6,
    Eggplant = 7,
    GoatCheese = 8,
    ChiefLove = 9
};

std::ostream &operator<<(std::ostream &os, const Ingredient &ingredient);
