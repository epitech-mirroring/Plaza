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

    bool operator==(Command &command2) {
        if (command != command2.command)
            return false;
        if (pizzas.front() != command2.pizzas.front())
            return false;
        if (sizes.front() != command2.sizes.front())
            return false;
        return true;
    }
};

Command &operator<<(Command &doneCommand, const Command &command) {
    for (auto pizza : command.pizzas) {
        doneCommand.pizzas.push_back(pizza);
    }
    for (auto size : command.sizes) {
        doneCommand.sizes.push_back(size);
    }
    for (auto command : command.command) {
        doneCommand.command.push_back(command);
    }
    return doneCommand;
}
