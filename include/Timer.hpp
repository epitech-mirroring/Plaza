/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <unistd.h>
#include <iostream>

enum TimerType {
    MICROSECONDS,
    MILLISECONDS,
    SECONDS
};

class Timer {
    public:
    static void wait(std::size_t timeToWait, TimerType type);
};
