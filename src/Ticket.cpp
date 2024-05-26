/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Ticket.hpp"

Ticket::Ticket(const Command& command, std::size_t pizzaIndex): _uuid(UUID()), _commandUuid(command.getUuid()), _pizza(command.getPizzas()[pizzaIndex]), _pizzaIndex(pizzaIndex), _isDone(false), _isBeingProcessed(false), _hasBeenAsked(false)
{
}

Ticket::Ticket(const UUID& ticketUuid, const UUID& commandUuid, const Pizza& pizza): _pizza(pizza) {
    this->_uuid = ticketUuid;
    this->_commandUuid = commandUuid;
    this->_pizza = pizza;
    this->_pizzaIndex = 0;
    this->_isDone = false;
    this->_isBeingProcessed = false;
    this->_hasBeenAsked = false;
}

Ticket::Ticket(const Ticket& other): _pizza(other._pizza) {
    this->_uuid = other._uuid;
    this->_commandUuid = other._commandUuid;
    this->_pizza = other._pizza;
    this->_pizzaIndex = other._pizzaIndex;
    this->_isDone = other._isDone;
    this->_isBeingProcessed = other._isBeingProcessed;
    this->_hasBeenAsked = other._hasBeenAsked;
}

const UUID& Ticket::getUuid() const {
    return this->_uuid;
}

void Ticket::setUuid(const UUID& uuid) {
    this->_uuid = uuid;
}

const UUID& Ticket::getCommandUuid() const {
    return this->_commandUuid;
}

void Ticket::setCommandUuid(const UUID& commandUuid) {
    this->_commandUuid = commandUuid;
}

const Pizza& Ticket::getPizza() const {
    return this->_pizza;
}

void Ticket::setPizza(const Pizza& pizza) {
    this->_pizza = pizza;
}

std::size_t Ticket::getPizzaIndex() const {
    return this->_pizzaIndex;
}

void Ticket::setPizzaIndex(std::size_t pizzaIndex) {
    this->_pizzaIndex = pizzaIndex;
}

bool Ticket::isDone() const {
    return this->_isDone;
}

void Ticket::setDone(bool isDone) {
    this->_isDone = isDone;
}

bool Ticket::isBeingProcessed() const {
    return this->_isBeingProcessed;
}

void Ticket::setBeingProcessed(bool isBeingProcessed) {
    this->_isBeingProcessed = isBeingProcessed;
}

bool Ticket::hasBeenAsked() const {
    return this->_hasBeenAsked;
}

void Ticket::setHasBeenAsked(bool hasBeenAsked) {
    this->_hasBeenAsked = hasBeenAsked;
}

Ticket& Ticket::operator=(const Ticket& other) {
    if (this == &other)
        return *this;
    this->_uuid = other._uuid;
    this->_commandUuid = other._commandUuid;
    this->_pizza = other._pizza;
    this->_pizzaIndex = other._pizzaIndex;
    this->_isDone = other._isDone;
    this->_isBeingProcessed = other._isBeingProcessed;
    this->_hasBeenAsked = other._hasBeenAsked;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Ticket& ticket) {
    return os << "Ticket{uuid=" << ticket.getUuid() << ", commandUuid=" << ticket.getCommandUuid() << ", pizza=" << ticket.getPizza() << ", pizzaIndex=" << ticket.getPizzaIndex() << ", isDone=" << ticket.isDone() << ", isBeingProcessed=" << ticket.isBeingProcessed() << "}";
}

bool Ticket::operator==(const Ticket& other) const {
    if (this == &other)
        return true;
    return this->_uuid == other._uuid && this->_commandUuid == other._commandUuid;
}
