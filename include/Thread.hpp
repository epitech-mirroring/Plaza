/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <pthread.h>
#include <functional>

class Thread {
protected:
    pthread_t _thread;
public:
    Thread();
    ~Thread();
    void start(const std::function<void *(void *)>& func, void *arg);
    void join();
    void detach();
    pthread_t getThread() const;
};
