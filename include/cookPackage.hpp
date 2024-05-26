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
    Ticket *ticket;
    float timeToCook;
    Cooks *cooker;
    std::vector<Ticket> *_doneCommandsList;
    CookPackage(Ticket *ticket, std::size_t timeToCook, Cooks *cooker, std::vector<Ticket> *doneCommandsList) : ticket(ticket), timeToCook(timeToCook), cooker(cooker), _doneCommandsList(doneCommandsList) {}
};
