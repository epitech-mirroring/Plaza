/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Cooks.hpp"
#include <unistd.h>

Cooks::Cooks()
{
    _isCooking = false;
}

Cooks::~Cooks()
{
}

void Cooks::cook(std::string pizzaName, std::size_t timeToCook)
{
    _isCooking = true;
    std::cout << "Cooking " << pizzaName << "for " << timeToCook << " micro seconds" << std::endl;
    usleep(timeToCook);
    _isCooking = false;
    std::cout << pizzaName << " is ready" << std::endl;
    // send information to the kitchen
}

bool Cooks::getIsCooking()
{
    return _isCooking;
}
