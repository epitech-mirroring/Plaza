/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Cooks.hpp"
#include "Pizza.hpp"
#include "Timer.hpp"

Cooks::Cooks()
{
    _isCooking = false;
}

void Cooks::cook(PizzaType pizza, PizzaSize size, std::size_t timeToCook)
{
    _isCooking = true;
    std::cout << "Cooking an " << size << " " << pizza << std::endl;
    Timer::wait(timeToCook, MICROSECONDS);
    _isCooking = false;
    std::cout << pizza << " " << size << " has been cook with love" << std::endl;
    // send information to the kitchen
}

bool Cooks::getIsCooking()
{
    return _isCooking;
}
