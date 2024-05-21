/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Cooks.hpp"
#include "Timer.hpp"
#include "cookPackage.hpp"

Cooks::Cooks()
{
    _isCooking = false;
}

void *Cooks::cook(void *param)
{
    struct CookPackage *cookPackage = (struct CookPackage *)param;
    cookPackage->cooker->_isCooking = true;
    std::cout << "Cooking an " << cookPackage->command.pizzas.front().getSize() << " " << cookPackage->command.pizzas.front().getType() << std::endl;
    Timer::wait(cookPackage->timeToCook, MICROSECONDS);
    cookPackage->cooker->_isCooking = false;
    std::cout << cookPackage->command.pizzas.front().getType() << " " << cookPackage->command.pizzas.front().getSize() << " has been cook with love" << std::endl;

    Command command = cookPackage->command;
    cookPackage->_doneCommandsList->push_back(command);
    delete cookPackage;
    return nullptr;
}

bool Cooks::getIsCooking()
{
    return _isCooking;
}
