/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <regex>
#include <sstream>
#include "Format.hpp"
#include "SlaveTicketBoard.hpp"

SlaveTicketBoard::SlaveTicketBoard(): AbstractTicketBoard(Role::SLAVE) {

}

SlaveTicketBoard::~SlaveTicketBoard() = default;

void SlaveTicketBoard::_handleMaster(const std::string &message) {
    // Try to parse the message
    std::vector<std::string> splitMessage = Format::split(message, '\n');
    for (const auto &msg : splitMessage) {
        if (msg.empty()) {
            continue;
        }
        for (const auto &[type, pair]: MESSAGE_TYPE_TO_STRING) {
            const auto &[f_string, regex] = pair;
            // Create a regex object
            std::regex reg(regex);

            // Check if the message match the regex
            if (std::regex_match(msg, reg)) {
                // Groupe 1 is the command UUID
                // Groupe 2 is the ticket UUID
                // We ignore the rest for now
                std::smatch match;
                std::regex_search(msg, match, reg);
                UUID command_uuid = UUID();
                command_uuid.fromString(match[1]);
                UUID ticket_uuid = UUID();
                ticket_uuid.fromString(match[2]);
                _mutex.lock();
                const Ticket *ticket = std::find_if(_tickets.begin(),
                                                    _tickets.end(),
                                                    [ticket_uuid](
                                                            const Ticket &ticket) {
                                                        return ticket.getUuid() ==
                                                               ticket_uuid;
                                                    }).base();
                _mutex.unlock();
                TicketEventType event_type = RELATION_MAP.at(type);
                for (const auto &callback: _callbacks[event_type]) {
                    callback(ticket, msg);
                }
            }
        }
    }
}

void SlaveTicketBoard::run()
{
    _isRunning = true;

    // Open the socket room
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in s_in{};
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(4242);
    s_in.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(_socket, (struct sockaddr *)&s_in, sizeof(s_in)) == -1)
        throw TicketBoardException("Failed to connect to the master ticket board");

    _thread.start([this](void *_) -> void * {
        fd_set readfds;
        fd_set writefds;
        timeval timeout = {0, 1000};
        while (_isRunning) {
            FD_ZERO(&readfds);
            FD_ZERO(&writefds);
            if (!_queue.empty()) {
                FD_SET(_socket, &writefds);
            } else {
                FD_SET(_socket, &readfds);
            }
            if (select(_socket + 1, &readfds, &writefds, nullptr, &timeout) == -1) {
                throw TicketBoardException("Failed to select");
            }
            if (FD_ISSET(_socket, &readfds)) {
                char buffer[1024];
                if (recv(_socket, buffer, 1024, 0) <= 0) {
                    throw TicketBoardException("Failed to receive message from the master ticket board");
                }

                _handleMaster(buffer);
            } else if (FD_ISSET(_socket, &writefds)) {
                std::string message = _queue.front();
                _queue.pop();
                if (send(_socket, message.c_str(), message.size(), 0) == -1) {
                    throw TicketBoardException("Failed to send message to the master ticket board");
                }
            }
        }
        return nullptr;
    }, nullptr);
}

void SlaveTicketBoard::markTicketAsDone(const UUID &uuid) {
    _mutex.lock();
    Ticket *ticket = std::find_if(_tickets.begin(), _tickets.end(), [uuid](const Ticket &ticket) {
        return ticket.getUuid() == uuid;
    }).base();

    if (ticket == nullptr) {
        _mutex.unlock();
        throw TicketBoardException("Failed to find ticket with UUID " + uuid.toString());
    }

    ticket->setBeingProcessed(false);
    ticket->setDone(true);
    _mutex.unlock();
    std::string formatedMessage = Format::formatString(TICKET_MARKED_AS_DONE_MESSAGE, ticket->getCommandUuid().toString().c_str(), ticket->getUuid().toString().c_str());
    _queue.push(formatedMessage);
}

void SlaveTicketBoard::markTicketAsBeingProcessed(const UUID &uuid) {
    _mutex.lock();
    Ticket *ticket = std::find_if(_tickets.begin(), _tickets.end(), [uuid](const Ticket &ticket) {
        return ticket.getUuid() == uuid;
    }).base();

    if (ticket == nullptr) {
        _mutex.unlock();
        throw TicketBoardException("Failed to find ticket with UUID " + uuid.toString());
    }

    ticket->setBeingProcessed(true);
    _mutex.unlock();
}

Thread *SlaveTicketBoard::operator->() {
    return &_thread;
}
