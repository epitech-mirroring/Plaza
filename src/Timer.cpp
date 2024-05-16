/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Timer.hpp"

void Timer::wait(std::size_t timeToWait, TimerType type)
{
    switch (type) {
        case MICROSECONDS:
            usleep(timeToWait);
            break;
        case MILLISECONDS:
            usleep(timeToWait * 1000);
            break;
        case SECONDS:
            usleep(timeToWait * 1000000);
            break;
    }
}
