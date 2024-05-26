/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Ticket.hpp"
#include "Thread.hpp"
#include "SlaveTicketBoard.hpp"

class Cooks {
protected:
    bool _isCooking;
    Thread _thread;
public:
    Cooks();
    ~Cooks() = default;
    void cook(Ticket ticket, float cookingTime);
    [[nodiscard]] bool getIsCooking() const;
    [[nodiscard]] Thread &getThread();
};
