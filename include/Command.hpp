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
    std::vector<Pizza> pizzas;

    bool operator==(Command &command2) {
        if (command != command2.command)
            return false;
        if (pizzas.front().getType() != command2.pizzas.front().getType())
            return false;
        if (pizzas.front().getSize() != command2.pizzas.front().getSize())
            return false;
        return true;
    }
    Command &operator<<(Command &command2) {
        for (auto pizza : command2.pizzas) {
            pizzas.push_back(pizza);
        }
        command2.pizzas.clear();
        return *this;
    }
};

