/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Timer.hpp"

void Timer::wait(float timeToWait, TimerType type)
{
    switch (type) {
        case MICROSECONDS:
            usleep((long) timeToWait);
            break;
        case MILLISECONDS:
            usleep((long) (timeToWait * 1000.0));
            break;
        case SECONDS:
            usleep((long) (timeToWait * 1000000.0));
            break;
    }
}
