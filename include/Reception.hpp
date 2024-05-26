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
    std::vector<Command *> _awaitingCommands;
    std::vector<Thread> _threads;
    bool _isRunning;
    Mutex _mutex;

    float _cookingTimeMultiplier;
    int _cooksPerKitchen;
    int _restockTime;
public:
    Reception(float cookingTimeMultiplier, int cooksPerKitchen, int restockTime);
    ~Reception();

    void run();

    void parseCommand(const std::string &command);
    void createKitchen();
};
