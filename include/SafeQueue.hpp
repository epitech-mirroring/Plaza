/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "Mutex.hpp"
#include <queue>

template <typename T>
class SafeQueue {
    public :
        SafeQueue() {
            _queue = std::queue<T>();
            _mutex = Mutex();
        };
        ~SafeQueue() = default;
        bool push(T &value) {
            if (_queue.size() >= _maxSize) {
                return false;
            }
            ScopedLock lock(_mutex);
            _queue.push(value);
            return true;
        };
        bool tryPop(T &value) {
            ScopedLock lock(_mutex);
            // std::cout << _queue.size() << std::endl;
            if (_queue.empty()) {
                return false;
            }
            value = _queue.front();
            _queue.pop();
            return true;
        };
        std::size_t size() {
            ScopedLock lock(_mutex);
            return _queue.size();
        };
        SafeQueue &operator=(const SafeQueue &safe_queue) {
            _queue = safeQueue._queue;
            _mutex = safeQueue._mutex;
            return *this;
        };
    private :
        std::queue<T> _queue;
        std::size_t _maxSize;
        Mutex _mutex;
};
