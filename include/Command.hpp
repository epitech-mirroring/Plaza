/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Pizza.hpp"
#include <vector>

struct Command {
    std::string command;
    std::vector<PizzaType> pizzas;
    std::vector<PizzaSize> sizes;
};

