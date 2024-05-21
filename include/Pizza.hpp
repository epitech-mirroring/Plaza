/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <iostream>

enum Ingredients {
    DOUGH = 1,
    TOMATO = 2,
    GRUYERE = 3,
    HAM = 4,
    MUSHROOMS = 5,
    STEAK = 6,
    EGGPLANT = 7,
    GOAT_CHEESE = 8,
    CHIEF_LOVE = 9
};

enum PizzaType {
    Regina = 1,
    Margarita = 2,
    Americana = 4,
    Fantasia = 8
};

enum PizzaSize {
    S = 1,
    M = 2,
    L = 4,
    XL = 8,
    XXL = 16
};

class Pizza {
    public:
        Pizza(PizzaType type, PizzaSize size);
        ~Pizza() = default;
        PizzaType getType() const;
        PizzaSize getSize() const;
        void setType(PizzaType type);
        void setSize(PizzaSize size);
    private:
        PizzaType _type;
        PizzaSize _size;
};

std::ostream &operator<<(std::ostream &os, PizzaType const &type);
std::ostream &operator<<(std::ostream &os, PizzaSize const &size);
std::ostream &operator<<(std::ostream &os, Pizza const &pizza);
