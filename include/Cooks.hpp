/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Pizza.hpp"
#include "Command.hpp"

class Cooks {
    public:
        Cooks(std::vector<Command> &_doneCommandsList);
        ~Cooks() = default;
        void *cook(void *param);
        bool getIsCooking();
    private:
        bool _isCooking;
        std::vector<Command> _doneCommandsList;
};
