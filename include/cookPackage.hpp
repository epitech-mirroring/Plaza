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

struct CookPackage {
    Command command;
    std::size_t timeToCook;
    Cooks *cooker;
    std::vector<Command> *_doneCommandsList;
};
