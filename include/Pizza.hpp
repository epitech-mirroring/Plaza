/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <iostream>

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

std::ostream &operator<<(std::ostream &os, PizzaType const &type)
{
    switch (type) {
        case Regina:
            os << "Regina";
            break;
        case Margarita:
            os << "Margarita";
            break;
        case Americana:
            os << "Americana";
            break;
        case Fantasia:
            os << "Fantasia";
            break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, PizzaSize const &size)
{
    switch (size) {
        case S:
            os << "S";
            break;
        case M:
            os << "M";
            break;
        case L:
            os << "L";
            break;
        case XL:
            os << "XL";
            break;
        case XXL:
            os << "XXL";
            break;
    }
    return os;
}
