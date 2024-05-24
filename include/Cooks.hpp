/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Ticket.hpp"

class Cooks {
    public:
        Cooks();
        ~Cooks() = default;
        static void *cook(void *param);
        bool getIsCooking() const;
    private:
        bool _isCooking;
};
