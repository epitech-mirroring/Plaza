/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Command.hpp"

Command::Command() {
    this->_uuid = UUID();
}

Command::Command(const Command &other) {
    this->_uuid = other._uuid;
    this->_pizzas = other._pizzas;
}

const UUID &Command::getUuid() const {
    return this->_uuid;
}

void Command::setUuid(const UUID &uuid) {
    this->_uuid = uuid;
}

const std::vector<Pizza> &Command::getPizzas() const {
    return this->_pizzas;
}

void Command::setPizzas(const std::vector<Pizza> &pizzas) {
    this->_pizzas = pizzas;
}

void Command::addPizza(const Pizza &pizza) {
    this->_pizzas.push_back(pizza);
}

void Command::removePizza(const Pizza &pizza) {
    this->_pizzas.erase(std::remove(this->_pizzas.begin(), this->_pizzas.end(), pizza), this->_pizzas.end());
}

bool Command::operator==(const Command &other) const {
    return this->_uuid == other._uuid;
}

bool Command::operator!=(const Command &other) const {
    return !(*this == other);
}

Command &Command::operator=(const Command &other) {
    if (this == &other)
        return *this;
    this->_uuid = other._uuid;
    this->_pizzas = other._pizzas;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Command &command) {
    os << command.getUuid();
    for (const auto &pizza : command.getPizzas())
        os << "\t -" << pizza << std::endl;
    return os;
}
