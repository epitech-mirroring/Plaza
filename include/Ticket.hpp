/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Command.hpp"

class Ticket {
protected:
    UUID _uuid;
    UUID _commandUuid;
    Pizza _pizza;
    std::size_t _pizzaIndex; // Index of the pizza in the command
    bool _isDone;
    bool _isBeingProcessed;

public:
    Ticket(const Command &command, std::size_t pizzaIndex);
    Ticket(const Ticket &other);

    [[nodiscard]] const UUID &getUuid() const;
    void setUuid(const UUID &uuid);
    [[nodiscard]] const UUID &getCommandUuid() const;
    void setCommandUuid(const UUID &commandUuid);
    [[nodiscard]] const Pizza &getPizza() const;
    void setPizza(const Pizza &pizza);
    [[nodiscard]] std::size_t getPizzaIndex() const;
    void setPizzaIndex(std::size_t pizzaIndex);
    [[nodiscard]] bool isDone() const;
    void setDone(bool isDone);
    [[nodiscard]] bool isBeingProcessed() const;
    void setBeingProcessed(bool isBeingProcessed);

    Ticket &operator=(const Ticket &other);
    friend std::ostream &operator<<(std::ostream &os, const Ticket &ticket);
};
