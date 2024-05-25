/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <unordered_map>
#include <queue>
#include <numeric>
#include "AbstractTicketBoard.hpp"
#include "Thread.hpp"

class SlaveTicketBoard : public AbstractTicketBoard {
protected:
    Thread _thread;
    std::queue<std::string> _queue;

    void _handleMaster(const std::string &message);
public:
    SlaveTicketBoard();
    ~SlaveTicketBoard() override;

    void run() override;
};
