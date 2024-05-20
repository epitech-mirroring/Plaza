/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Thread.hpp"
#include <bits/sigthread.h>
#include <pthread.h>
#include <cerrno>

Thread::Thread()
{
    pthread_mutex_init(&_mutex, NULL);
}

Thread::~Thread()
{
    pthread_mutex_destroy(&_mutex);
}

void Thread::create(void *(*start_routine)(void *), void *arg)
{
    pthread_mutex_lock(&_mutex);
    pthread_create(&_thread, NULL, start_routine, arg);
}

void Thread::join()
{
    pthread_join(_thread, NULL);
    pthread_mutex_unlock(&_mutex);
}

bool Thread::isRunning()
{
    if (pthread_mutex_trylock(&_mutex) != 0 && pthread_mutex_trylock(&_mutex) != EBUSY) {
        return true;
    }
    return false;
}

bool Thread::isDead()
{
    return !isRunning();
}
