/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "MasterTicketBoard.hpp"
#include "Command.hpp"

class Reception {
protected:
    MasterTicketBoard _ticketBoard;
    std::vector<Command> _awaitingCommands;
    bool _isRunning;

public:
    Reception();
    ~Reception();

    void run();

    void parseCommand(const std::string &command);
};
