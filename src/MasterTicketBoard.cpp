/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <regex>
#include "MasterTicketBoard.hpp"

MasterTicketBoard::MasterTicketBoard(): AbstractTicketBoard(MASTER) {

}

MasterTicketBoard::~MasterTicketBoard() = default;

void MasterTicketBoard::_acceptSlaves() {
    // Accept a new slave and add it to the list of slaves
    int slave_fd = accept(_socket, nullptr, nullptr);
    if (slave_fd == -1) {
        throw TicketBoardException("Failed to accept a new slave");
    }
    _slaves[slave_fd] = std::queue<std::string>();
}

void MasterTicketBoard::_handleSlave(int slave) {
    // Handle a slave by reading its message and sending it to all other slaves
    char buffer[1024];
    std::size_t size = recv(slave, buffer, 1024, 0);
    if (size == 0) {
        _slaves.erase(slave);
        close(slave);
    } else {
        std::string message(buffer, size);
        _handleMessage(message);
    }
}

void MasterTicketBoard::_handleMessage(const std::string &message) {
    // Handle a message received from a slave
    // The message should be a command to send to the slaves
    // The command should be sent to all slaves
    for (auto &[slave, queue] : _slaves) {
        queue.push(message);
    }

    // Try to parse the message
    for (const auto &[type, pair] : MESSAGE_TYPE_TO_STRING) {
        const auto &[f_string, regex] = pair;
        // Create a regex object
        std::regex reg(regex);

        // Check if the message match the regex
        if (std::regex_match(message, reg)) {
            // Groupe 1 is the command UUID
            // Groupe 2 is the ticket UUID
            // We ignore the rest for now
            std::smatch match;
            std::regex_search(message, match, reg);
            UUID command_uuid = UUID();
            command_uuid.fromString(match[1]);
            UUID ticket_uuid = UUID();
            ticket_uuid.fromString(match[2]);
            const Ticket *ticket = &std::find_if(_tickets.begin(), _tickets.end(), [ticket_uuid](const Ticket &ticket) {
                return ticket.getUuid() == ticket_uuid;
            })[0];

            TicketEventType event_type = RELATION_MAP.at(type);
            for (const auto &callback : _callbacks[event_type]) {
                callback(*ticket, message);
            }
        }
    }
}

void MasterTicketBoard::run() {
    // The master ticket board should open the socket room and wait for the slaves to connect
    // All message should be exchanged to all slaves connected (like a public chat)
    // The master ticket board should also be able to send command to the slaves

    _isRunning = true;

    // Open the socket room
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == -1) {
        throw TicketBoardException("Failed to open the socket room");
    }
    struct sockaddr_in addr{};
    int opt = 1;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4242);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1 ||
        bind(_socket, (struct sockaddr *)&addr, sizeof(addr)) == -1 ||
        listen(_socket, 10) == -1) {
        throw TicketBoardException("Failed to open the socket room");
    }

    _thread.start([this](void *_) -> void * {
        while (_isRunning) {
            fd_set readfds;
            fd_set writefds;
            timeval timeout = {0, 1000};
            FD_ZERO(&readfds);
            FD_ZERO(&writefds);
            int max_fd = std::accumulate(_slaves.begin(), _slaves.end(), _socket, [](int max, const auto &slave) {
                return std::max(max, slave.first);
            });
            max_fd = std::max(max_fd, _socket);
            for (const auto &[slave_fd, queue] : _slaves) {
                if (!queue.empty()) {
                    FD_SET(slave_fd, &writefds);
                } else {
                    FD_SET(slave_fd, &readfds);
                }
            }
            FD_SET(_socket, &readfds);
            if (select(max_fd + 1, &readfds, &writefds, nullptr, &timeout) == -1) {
                throw TicketBoardException("Failed to select");
            }
            if (FD_ISSET(_socket, &readfds)) {
                _acceptSlaves();
            }
            for (auto &[slave_fd, queue] : _slaves) {
                if (FD_ISSET(slave_fd, &readfds)) {
                    _handleSlave(slave_fd);
                }
                if (FD_ISSET(slave_fd, &writefds)) {
                    if (!queue.empty()) {
                        std::string message = queue.front();
                        queue.pop();
                        if (send(slave_fd, message.c_str(), message.size(), 0) == -1) {
                            throw TicketBoardException("Failed to write to a slave");
                        }
                    }
                }
            }
        }
        return nullptr;
    }, nullptr);
}
