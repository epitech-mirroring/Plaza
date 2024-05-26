/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <iostream>
#include "SlaveTicketBoard.hpp"
#include "Mutex.hpp"

struct CookPackage {
    Ticket *ticket;
    float timeToCook;
    SlaveTicketBoard *slaveTicketBoard;
    Mutex *mutex;
    CookPackage(Ticket *ticket, float timeToCook, SlaveTicketBoard *slaveTicketBoard, Mutex *mutex)
    {
        this->ticket = ticket;
        this->timeToCook = timeToCook;
        this->slaveTicketBoard = slaveTicketBoard;
        this->mutex = mutex;
    }
};
