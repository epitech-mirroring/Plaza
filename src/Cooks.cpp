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
    auto *cookPackage = (struct CookPackage *)param;
    Ticket ticket = Ticket(cookPackage->ticket->getUuid(), cookPackage->ticket->getCommandUuid(), cookPackage->ticket->getPizza());
    ticket.setBeingProcessed(true);
    ticket.setDone(false);
    std::cout << ticket.getUuid() << std::endl << std::endl;
    cookPackage->cooker->_isCooking = true;
    std::cout << "Cooking an " << cookPackage->ticket->getPizza().getSize() << " " << cookPackage->ticket->getPizza().getType() << std::endl;
    Timer::wait(cookPackage->timeToCook, SECONDS);
    cookPackage->cooker->_isCooking = false;
    std::cout << ticket.getUuid() << " has been cook with love" << std::endl;

    cookPackage->ticket->setBeingProcessed(false);
    cookPackage->ticket->setDone(true);
    cookPackage->_doneCommandsList->push_back(ticket);
    delete cookPackage;
    return nullptr;
}

bool Cooks::getIsCooking() const
{
    return _isCooking;
}
