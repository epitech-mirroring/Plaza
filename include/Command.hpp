/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "UUID.hpp"
#include <vector>
#include "Pizza.hpp"

class Command {
protected:
    UUID _uuid;
    std::vector<Pizza> _pizzas;
public:
    Command();
    Command(const Command &other);
    ~Command() = default;

    [[nodiscard]] const UUID &getUuid() const;
    void setUuid(const UUID &uuid);
    [[nodiscard]] const std::vector<Pizza> &getPizzas() const;
    void setPizzas(const std::vector<Pizza> &pizzas);
    void addPizza(const Pizza &pizza);
    void removePizza(const Pizza &pizza);
    bool operator==(const Command &other) const;
    bool operator!=(const Command &other) const;
    Command &operator=(const Command &other);

    friend std::ostream &operator<<(std::ostream &os, const Command &command);
};
