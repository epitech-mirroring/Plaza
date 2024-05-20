/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Kitchen.hpp"
#include "cookPackage.hpp"

Kitchen::Kitchen(std::size_t nbCooksMax, std::size_t refillTime, std::size_t cookTimeMultiplier)
{
    _nbCooksMax = nbCooksMax;
    _refillTime = refillTime;
    _cookTimeMultiplier = cookTimeMultiplier;
    _lastRefill = time(NULL);
    _lastWork = time(NULL);
    _commandQueue = std::vector<Command>();
    _doneCommands = std::vector<Command>();
    _stocks = {5, 5, 5, 5, 5, 5, 5, 5, 5};
    for (std::size_t i = 0; i < _nbCooksMax; i++) {
        Cooks *cooker = new Cooks(_doneCommands);
        coockersStruct cookerStruct = {cooker, Thread()};
        _cookers.push_back(cookerStruct);
    }
}

void Kitchen::refill()
{
    if (time(NULL) - _lastRefill >= _refillTime / 1000) {
        _stocks.dough++;
        _stocks.tomato++;
        _stocks.gruyere++;
        _stocks.ham++;
        _stocks.mushrooms++;
        _stocks.steak++;
        _stocks.eggplant++;
        _stocks.goatCheese++;
        _stocks.chiefLove++;
        _lastRefill = time(NULL);
    }
}

bool Kitchen::addCommand(Command command)
{
    if (_commandQueue.size() >= 2 * _nbCooksMax)
        return false;
    _commandQueue.push_back(command);
    return true;
}

std::size_t Kitchen::getCommandQueueSize()
{
    return _commandQueue.size();
}

void Kitchen::loop()
{
    while (_lastWork - time(NULL) < 5) {
        refill();
        // updateCommands();
    }
}

void Kitchen::updateCommands()
{
    if (_commandQueue.size() > 0) {
        for (auto command : _commandQueue){
            if (!canCook(command.pizzas.front()))
                continue;
            for (auto cooker : _cookers) {
                if (cooker.cooker->getIsCooking())
                    continue;
                cookPackage package;
                package.command = command.command;
                package.pizza = command.pizzas.front();
                package.size = command.sizes.front();
                if (package.pizza == Regina) {
                    package.timeToCook = 2;
                } else {
                    package.timeToCook = package.pizza / 2;
                }
                package.timeToCook *= _cookTimeMultiplier;
                package.cooker = cooker.cooker;
                cooker.thread.create((void *(*)(void *))Cooks::cook((void*)&package), (void*)&package);
                removeIngredients(package.pizza);
                _commandQueue.erase(findCommand(command));
            }
        }
    }
    //todo send done command to reception
    return;
}

bool Kitchen::canCook(PizzaType pizzaType)
{
    if (pizzaType == Regina) {
        if (_stocks.dough >= 1 && _stocks.tomato >= 1 && _stocks.gruyere >= 1 && _stocks.ham >= 1 && _stocks.mushrooms >= 1)
            return true;
    } else if (pizzaType == Margarita) {
        if (_stocks.dough >= 1 && _stocks.tomato >= 1 && _stocks.gruyere >= 1)
            return true;
    } else if (pizzaType == Americana) {
        if (_stocks.dough >= 1 && _stocks.tomato >= 1 && _stocks.gruyere >= 1 && _stocks.steak >= 1)
            return true;
    } else if (pizzaType == Fantasia) {
        if (_stocks.dough >= 1 && _stocks.tomato >= 1 && _stocks.eggplant >= 1 && _stocks.goatCheese >= 1 && _stocks.chiefLove >= 1)
            return true;
    }
    return false;
}

void Kitchen::removeIngredients(PizzaType pizzaType)
{
    if (pizzaType == Regina) {
        _stocks.dough--;
        _stocks.tomato--;
        _stocks.gruyere--;
        _stocks.ham--;
        _stocks.mushrooms--;
    } else if (pizzaType == Margarita) {
        _stocks.dough--;
        _stocks.tomato--;
        _stocks.gruyere--;
    } else if (pizzaType == Americana) {
        _stocks.dough--;
        _stocks.tomato--;
        _stocks.gruyere--;
        _stocks.steak--;
    } else if (pizzaType == Fantasia) {
        _stocks.dough--;
        _stocks.tomato--;
        _stocks.eggplant--;
        _stocks.goatCheese--;
        _stocks.chiefLove--;
    }
}

std::vector<Command>::const_iterator Kitchen::findCommand(Command command) {
    std::size_t i = 0;
    for (; i < _commandQueue.size(); i++) {
        if (command == _commandQueue[i])
            break;
    }
    return _commandQueue.begin() + i;
}
