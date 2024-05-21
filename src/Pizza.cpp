/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Pizza.hpp"

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

Pizza::Pizza(PizzaType type, PizzaSize size)
{
    _type = type;
    _size = size;
}

PizzaType Pizza::getType() const
{
    return _type;
}

PizzaSize Pizza::getSize() const
{
    return _size;
}

void Pizza::setType(PizzaType type)
{
    _type = type;
}

void Pizza::setSize(PizzaSize size)
{
    _size = size;
}

std::ostream &operator<<(std::ostream &os, Pizza const &pizza)
{
    os << pizza.getType() << " " << pizza.getSize();
    return os;
}

