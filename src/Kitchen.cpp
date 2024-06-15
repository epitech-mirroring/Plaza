/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <chrono>
#include <regex>
#include "Kitchen.hpp"
#include "cookPackage.hpp"

Kitchen::Kitchen(std::size_t nbCooksMax, std::chrono::milliseconds refillTime, float cookTimeMultiplier)
{
    _nbCooksMax = nbCooksMax;
    _refillTime = refillTime;
    _cookTimeMultiplier = cookTimeMultiplier;
    _lastRefill = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    _lastWork = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
    for (std::size_t i = 0; i < INGREDIENTS_COUNT; i++) {
        _ingredients[(Ingredient)(i + 1)] = 5;
    }
    for (std::size_t i = 0; i < _nbCooksMax; i++) {
        auto *cooker = new Cooks();
        _cookers.push_back(cooker);
    }
    _hasMadeAtLeastOnePizza = false;
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

bool Kitchen::addTicket(Ticket *ticket)
{
    if (getCountOfCurrentlyCookingCooks() >= _nbCooksMax)
        return false;
    _slaveTicketBoard.addTicket(ticket);
    return true;
}

bool Kitchen::shouldTerminate() {
    _lastWorkMutex.lock();
    bool shouldTerminate = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()) - _lastWork >= std::chrono::seconds(5);
    _lastWorkMutex.unlock();
    shouldTerminate = shouldTerminate && _hasMadeAtLeastOnePizza;
    if (shouldTerminate) {
        for (auto cooker : _cookers) {
            cooker->getThread().join();
        }
    }
    return shouldTerminate;
}

void Kitchen::loop()
{
    _slaveTicketBoard.run();
    _slaveTicketBoard.addListener([this](const Ticket *ticket, const std::string &msg) {
        std::regex reg(NEW_TICKET_REGEX);
        std::smatch match;
        if (std::regex_match(msg, match, reg)) {
            UUID command;
            UUID ticket_uuid;
            command.fromString(match[1]);
            ticket_uuid.fromString(match[2]);
            Pizza::Type type = Pizza::parseType(match[3]);
            Pizza::Size size = Pizza::parseSize(match[4]);
            std::cout << "New ticket received: " << ticket_uuid.toString() << std::endl;
            Ticket *newTicket = new Ticket(ticket_uuid, command, Pizza(type, size));
            addTicket(newTicket);
        }
    }, AbstractTicketBoard::TicketEventType::ADDED);
    while (!shouldTerminate()) {
        refill();
        updateTickets();
    }
    _slaveTicketBoard.stop();
    _slaveTicketBoard->join();
}

void Kitchen::updateTickets()
{
    for (auto ticket : _slaveTicketBoard.getTickets()) {
        usleep(10);
        if (!canCook(ticket->getPizza().getType()) || ticket->isBeingProcessed() || ticket->isDone())
            continue;
        for (auto cooker : _cookers) {
            if (cooker->getIsCooking())
                continue;
            float cookingTime = 0.f;
            if (ticket->getPizza().getType() == Pizza::Regina) {
                cookingTime = 2.f;
            } else {
                cookingTime = (float) ticket->getPizza().getType() / 2.f;
            }
            cookingTime *= _cookTimeMultiplier;
            cooker->getThread().start([this, ticket, cooker, cookingTime](void *_) {
                if (ticket->isDone() || ticket->isBeingProcessed())
                    return nullptr;
                this->_slaveTicketBoard.markTicketAsBeingProcessed(ticket->getUuid());
                cooker->cook(ticket, cookingTime);
                this->_slaveTicketBoard.markTicketAsDone(ticket->getUuid());
                return nullptr;
            }, nullptr);
            removeIngredients(ticket->getPizza().getType());
            _lastWorkMutex.lock();
            _lastWork = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
            _lastWorkMutex.unlock();
            this->_hasMadeAtLeastOnePizza = true;
            break;
        }
    }
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

std::size_t Kitchen::getCountOfCurrentlyCookingCooks() const
{
    std::size_t count = 0;
    for (const auto cooker : _cookers) {
        if (cooker->getIsCooking())
            count++;
    }
    return count;
}
