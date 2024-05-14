/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <iostream>

class Cooks {
    public:
        Cooks();
        ~Cooks();
        void cook(std::string pizzaName, std::size_t timeToCook);
        bool getIsCooking();
    private:
        bool _isCooking;
};
