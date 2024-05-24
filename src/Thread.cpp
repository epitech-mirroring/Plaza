/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Thread.hpp"

Thread::Thread() {
    _thread = 0;
}

Thread::~Thread() {
    if (_thread)
        pthread_detach(_thread);
}

struct ThreadArgs {
    std::function<void *(void *)> func;
    void *arg{};
};

static void *middleman(void *arg) {
    auto *args = reinterpret_cast<ThreadArgs *>(arg);
    auto *ret = args->func(args->arg);
    delete args;
    return ret;
}

void Thread::start(const std::function<void *(void *)>& func, void *arg) {
    auto *args = new ThreadArgs{func, arg};
    pthread_create(&_thread, nullptr, middleman, args);
}

void Thread::join() {
    pthread_join(_thread, nullptr);
}

void Thread::detach() {
    pthread_detach(_thread);
}

pthread_t Thread::getThread() const {
    return _thread;
}
