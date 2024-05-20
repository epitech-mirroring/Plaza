/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Cooks.hpp"
#include "Command.hpp"
#include "SafeQueue.hpp"
#include "Thread.cpp"

struct coockersStruct {
    Cooks *cooker;
    Thread thread;
};

struct stocks {
    std::size_t dough;
    std::size_t tomato;
    std::size_t gruyere;
    std::size_t ham;
    std::size_t mushrooms;
    std::size_t steak;
    std::size_t eggplant;
    std::size_t goatCheese;
    std::size_t chiefLove;
};

class Kitchen {
protected:
    std::vector<Command> _commandQueue;
    std::vector<Command> _doneCommands;
    std::vector<coockersStruct> _cookers;
    std::size_t _nbCooksMax;
    std::size_t _refillTime;
    std::size_t _lastRefill;
    std::size_t _lastWork;
    std::size_t _cookTimeMultiplier;
    stocks _stocks;
public:
    Kitchen(std::size_t nbCooksMax, std::size_t refillTime, std::size_t cookTimeMultiplier);
    ~Kitchen() = default;
    void refill();
    bool addCommand(Command command);
    std::size_t getCommandQueueSize();
    void loop();
    void updateCommands();
    bool canCook(PizzaType pizzaType);
    void removeIngredients(PizzaType pizzaType);
    std::vector<Command>::const_iterator findCommand(Command);
};
