/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Kitchen.hpp"
#include "cookPackage.hpp"
#include <chrono>

Kitchen::Kitchen(std::size_t nbCooksMax, std::chrono::milliseconds refillTime, std::size_t cookTimeMultiplier)
{
    _nbCooksMax = nbCooksMax;
    _refillTime = refillTime;
    _cookTimeMultiplier = cookTimeMultiplier;
    _lastRefill = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    _lastWork = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
    _ticketQueue = std::vector<Ticket>();
    _doneTickets = std::vector<Ticket>();
    for (std::size_t i = 0; i < INGREDIENTS_COUNT; i++) {
        _ingredients[(Ingredient)(i + 1)] = 5;
    }
    for (std::size_t i = 0; i < _nbCooksMax; i++) {
        Cooks *cooker = new Cooks();
        coockersStruct cookerStruct = {cooker, Thread()};
        _cookers.push_back(cookerStruct);
    }
}

void Kitchen::refill()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - _lastRefill >= _refillTime) {
        for (std::size_t i = 0; i < INGREDIENTS_COUNT; i++) {
            _ingredients[(Ingredient)(i + 1)]++;
        }
        _lastRefill = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    }
}

bool Kitchen::addTicket(Ticket &ticket)
{
    if (_ticketQueue.size() >= 2 * _nbCooksMax)
        return false;
    _ticketQueue.push_back(ticket);
    std::cout << "New ticket " << ticket.getUuid() << " added to the queue" << std::endl;
    return true;
}

std::size_t Kitchen::getTicketQueueSize()
{
    return _ticketQueue.size();
}

void Kitchen::loop()
{
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()) - _lastWork < std::chrono::seconds(5)) {
        refill();
        updateTickets();
    }
}

void Kitchen::updateTickets()
{
    if (_ticketQueue.size() <= 0)
        return;
    for (auto &ticket : _ticketQueue) {
        if (!canCook(ticket.getPizza().getType()) || ticket.isBeingProcessed() || ticket.isDone())
            continue;
        for (auto cooker : _cookers) {
            if (cooker.cooker->getIsCooking())
                continue;
            ticket.setBeingProcessed(true);
            CookPackage *package = new CookPackage(&ticket, 0, cooker.cooker, &_doneTickets);
            if (package->ticket->getPizza().getType() == Pizza::Regina) {
                package->timeToCook = 2;
            } else {
                package->timeToCook = package->ticket->getPizza().getType() / 2;
            }
            package->timeToCook *= _cookTimeMultiplier;
            cooker.thread.create(Cooks::cook, (void*)package);
            removeIngredients(ticket.getPizza().getType());
            _lastWork = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
            break;
        }
    }
    for (auto &ticket : _ticketQueue) {
        if (ticket.isDone()) {
            auto it = findTicket(ticket);
            _ticketQueue.erase(it);
        }
    }
    //todo send done command to reception
    return;
}

bool Kitchen::canCook(Pizza::Type pizzaType)
{
    for (auto ingredient : RECIPIES.at(pizzaType).getIngredients()) {
        if (_ingredients[ingredient] == 0)
            return false;
    }
    return true;
}

void Kitchen::removeIngredients(Pizza::Type pizzaType)
{
    for (auto ingredient : RECIPIES.at(pizzaType).getIngredients()) {
        _ingredients[ingredient]--;
    }
}

std::vector<Ticket>::const_iterator Kitchen::findTicket(Ticket &ticket) {
    std::size_t i = 0;
    for (; i < _ticketQueue.size(); i++) {
        if (ticket == _ticketQueue[i])
            break;
    }
    return _ticketQueue.begin() + i;
}
