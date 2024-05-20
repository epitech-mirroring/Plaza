/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <iostream>
#include "Cooks.hpp"

struct cookPackage {
    PizzaType pizza;
    PizzaSize size;
    std::size_t timeToCook;
    Cooks *cooker;
};
