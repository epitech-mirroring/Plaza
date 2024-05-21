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
    _commandQueue = std::vector<Command>();
    _doneCommands = std::vector<Command>();
    _stocks = {5, 5, 5, 5, 5, 5, 5, 5, 5};
    for (std::size_t i = 0; i < _nbCooksMax; i++) {
        Cooks *cooker = new Cooks();
        coockersStruct cookerStruct = {cooker, Thread()};
        _cookers.push_back(cookerStruct);
    }
}

void Kitchen::refill()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - _lastRefill >= _refillTime) {
        _stocks.dough++;
        _stocks.tomato++;
        _stocks.gruyere++;
        _stocks.ham++;
        _stocks.mushrooms++;
        _stocks.steak++;
        _stocks.eggplant++;
        _stocks.goatCheese++;
        _stocks.chiefLove++;
        _lastRefill = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    }
}

bool Kitchen::addCommand(Command &command)
{
    if (_commandQueue.size() >= 2 * _nbCooksMax)
        return false;
    _commandQueue.push_back(command);
    std::cout << "New command " << command.command << " added to the queue" << std::endl;
    return true;
}

std::size_t Kitchen::getCommandQueueSize()
{
    return _commandQueue.size();
}

void Kitchen::loop()
{
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()) - _lastWork < std::chrono::seconds(5)) {
        refill();
        updateCommands();
    }
}

void Kitchen::updateCommands()
{
    if (_commandQueue.size() > 0) {
        for (auto command : _commandQueue) {
            if (!canCook(command.pizzas.front().getType()))
                continue;
            for (auto cooker : _cookers) {
                if (cooker.cooker->getIsCooking())
                    continue;
                CookPackage *package = new CookPackage();
                package->_doneCommandsList = &_doneCommands;
                package->command.pizzas.push_back(command.pizzas.front());
                if (package->command.pizzas.front().getType() == Regina) {
                    package->timeToCook = 2;
                } else {
                    package->timeToCook = package->command.pizzas.front().getType() / 2;
                }
                package->timeToCook *= _cookTimeMultiplier;
                package->cooker = cooker.cooker;
                cooker.thread.create(Cooks::cook, (void*)package);
                removeIngredients(package->command.pizzas.front().getType());
                _commandQueue.erase(findCommand(command));
                _lastWork = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
                break;
            }
            if (_commandQueue.size() == 0)
                return;
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
