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

class Thread {
    public :
        Thread();
        ~Thread();
        void create(void *(*start_routine)(void *), void *arg);
        void join();
        bool isRunning();
        bool isDead();
    private :
        pthread_t _thread;
        pthread_mutex_t _mutex;
};
