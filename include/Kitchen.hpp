/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Cooks.hpp"
#include "SafeQueue.hpp"
#include "Thread.hpp"
#include "Recipe.hpp"
#include "SlaveTicketBoard.hpp"
#include <chrono>
#include <map>

struct CoockersStruct {
    Cooks *cooker;
    Thread thread;
};

class Kitchen {
protected:
    std::vector<Ticket> _ticketQueue;
    std::vector<Ticket> _doneTickets;
    std::vector<CoockersStruct> _cookers;
    std::size_t _nbCooksMax;
    std::chrono::milliseconds _refillTime;
    std::chrono::milliseconds _lastRefill;
    std::chrono::seconds _lastWork;
    float _cookTimeMultiplier;
    std::map<Ingredient, std::size_t> _ingredients;
    SlaveTicketBoard _slaveTicketBoard;
public:
    Kitchen(std::size_t nbCooksMax, std::chrono::milliseconds refillTime, float cookTimeMultiplier);
    ~Kitchen() = default;
    void refill();
    bool addTicket(Ticket &ticket);
    std::size_t getTicketQueueSize();
    void loop();
    void updateTickets();
    bool canCook(Pizza::Type pizzaType);
    void removeIngredients(Pizza::Type pizzaType);
    std::vector<Ticket>::const_iterator findTicket(Ticket &ticket);
};
