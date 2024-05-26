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

class Kitchen {
protected:
    std::vector<Cooks *> _cookers;
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
    bool addTicket(Ticket *ticket);
    void loop();
    void updateTickets();
    bool canCook(Pizza::Type pizzaType);
    void removeIngredients(Pizza::Type pizzaType);

    [[nodiscard]] std::size_t getCountOfCurrentlyCookingCooks() const;
};
