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

class MasterTicketBoard : public AbstractTicketBoard {
protected:
    Thread _thread;
    std::unordered_map<int, std::queue<std::string>> _slaves;

    void _acceptSlaves();
    void _handleSlave(int slave);
    void _handleMessage(const std::string &message, int sender);
public:
    MasterTicketBoard();
    ~MasterTicketBoard() override;

    void run() override;

    void addCommand(const Command &command) override;

    Thread *operator->();
};
