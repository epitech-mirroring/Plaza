/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Mutex.hpp"

class ScopedLock {
    public :
        ScopedLock(Mutex &mutex);
        ~ScopedLock();
    private :
        Mutex &_mutex;
};
