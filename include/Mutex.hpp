/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <threads.h>
#include <bits/pthreadtypes.h>
#include <signal.h>
#include <pthread.h>

class Mutex {
    public :
        Mutex();
        Mutex(const Mutex &mutex);
        ~Mutex();
        void lock();
        void unlock();
        void trylock();
        Mutex &operator=(const Mutex &mutex);
    private :
        pthread_mutex_t _mutex;
};