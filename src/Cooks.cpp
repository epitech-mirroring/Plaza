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
    std::cout << "Cooking an " << cookPackage->ticket->getPizza().getSize() << " " << cookPackage->ticket->getPizza().getType() << std::endl;
    Timer::wait(cookPackage->timeToCook, MICROSECONDS);
    cookPackage->cooker->_isCooking = false;
    std::cout << cookPackage->ticket->getPizza().getType() << " " << cookPackage->ticket->getPizza().getSize() << " has been cook with love" << std::endl;

    cookPackage->_doneCommandsList->push_back(*cookPackage->ticket);
    cookPackage->ticket->setBeingProcessed(false);
    cookPackage->ticket->setDone(true);
    delete cookPackage;
    return nullptr;
}

bool Cooks::getIsCooking()
{
    return _isCooking;
}
