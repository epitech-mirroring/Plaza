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

Cooks::Cooks(std::vector<Command> &_doneCommandsList)
{
    _isCooking = false;
    _doneCommandsList = _doneCommandsList;
}

void *Cooks::cook(void *param)
{
    struct cookPackage cookPackage = *(struct cookPackage *)param;
    // cookPackage.cooker->_isCooking = true;
    std::cout << "Cooking an " << cookPackage.size << " " << cookPackage.pizza << std::endl;
    Timer::wait(cookPackage.timeToCook, MICROSECONDS);
    // cookPackage.cooker->_isCooking = false;
    std::cout << cookPackage.pizza << " " << cookPackage.size << " has been cook with love" << std::endl;
    // send information to the kitchen
    Command command;
    command.pizzas.push_back(cookPackage.pizza);
    command.sizes.push_back(cookPackage.size);
    command.command = cookPackage.command;
    _doneCommandsList.push_back(command);
    return nullptr;
}

bool Cooks::getIsCooking()
{
    return _isCooking;
}
