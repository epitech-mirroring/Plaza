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
    _ticketQueue = std::vector<Ticket>();
    _doneTickets = std::vector<Ticket>();
    for (std::size_t i = 0; i < INGREDIENTS_COUNT; i++) {
        _ingredients[(Ingredient)(i + 1)] = 5;
    }
    for (std::size_t i = 0; i < _nbCooksMax; i++) {
        auto *cooker = new Cooks();
        CoockersStruct cookerStruct = {cooker, Thread()};
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
    this->_ticketQueueMutex.lock();
    std::cout << "New ticket " << ticket.getUuid() << " added to the queue" << std::endl;
    _ticketQueue.push_back(ticket);
    _slaveTicketBoard.addTicket(ticket);
    this->_ticketQueueMutex.unlock();
    return true;
}

std::size_t Kitchen::getTicketQueueSize()
{
    return _ticketQueue.size();
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
            Ticket newTicket(ticket_uuid, command, Pizza(type, size));
            addTicket(newTicket);
        }
    }, AbstractTicketBoard::TicketEventType::ADDED);
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()) - _lastWork < std::chrono::seconds(5)) {
        refill();
        updateTickets();
    }
    _slaveTicketBoard.stop();
    _slaveTicketBoard->join();
}

void Kitchen::updateTickets()
{
    if (_ticketQueue.empty())
        return;
    for (auto& ticket : _ticketQueue) {
        if (!canCook(ticket.getPizza().getType()) || ticket.isBeingProcessed() || ticket.isDone())
            continue;
        for (auto cooker : _cookers) {
            if (cooker.cooker->getIsCooking())
                continue;
            auto *package = new CookPackage(&ticket, 0, cooker.cooker, &_doneTickets);
            if (package->ticket->getPizza().getType() == Pizza::Regina) {
                package->timeToCook = 2.f;
            } else {
                package->timeToCook = (float) package->ticket->getPizza().getType() / 2.f;
            }
            package->timeToCook *= _cookTimeMultiplier;
            ticket.setBeingProcessed(true);
            std::cout << ticket.getUuid() << std::endl;
            cooker.thread.start(Cooks::cook, package);
            removeIngredients(ticket.getPizza().getType());
            _lastWork = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
            break;
        }
    }
    this->_ticketQueueMutex.lock();
    for (auto &ticketDone : _doneTickets) {
        _slaveTicketBoard.markTicketAsDone(ticketDone.getUuid());
        for (auto &ticket : _ticketQueue) {
            if (ticket == ticketDone) {
                ticket.setDone(true);
                ticket.setBeingProcessed(false);
                auto it = findTicket(ticket);
                _ticketQueue.erase(it);
            }
        }
    }
    _doneTickets.clear();
    this->_ticketQueueMutex.unlock();
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
