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
    _thread = Thread();
}

void Cooks::cook(Ticket *ticket, float cookingTime)
{
    this->_isCooking = true;
    std::cout << "Cooking an " << ticket->getPizza().getSize() << " " << ticket->getPizza().getType() << std::endl;
    Timer::wait(cookingTime, SECONDS);
    std::cout << ticket->getUuid() << " (" << ticket->getPizza() << ") has been cook with love" << std::endl;
    this->_isCooking = false;
}

bool Cooks::getIsCooking() const
{
    return _isCooking;
}

Thread &Cooks::getThread()
{
    return _thread;
}
