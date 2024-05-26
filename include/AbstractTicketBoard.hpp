/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <functional>
#include "Ticket.hpp"

#define NEW_TICKET_MESSAGE "[{}-{}] New ticket, type: {}, size: {}\n"
#define TICKET_REQUEST_ASSIGNMENT_MESSAGE "[{}-{}] Kitchen {} requested ticket assignment\n"
#define TICKET_ASSIGNED_MESSAGE "[{}-{}] Ticket assigned to kitchen {}\n"
#define TICKET_MARKED_AS_DONE_MESSAGE "[{}-{}] Ticket marked as done\n"

#define UUID_REGEX "[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}"
#define NEW_TICKET_REGEX "\\[(" UUID_REGEX ")-(" UUID_REGEX ")\\] New ticket, type: (Regina|Margarita|Americana|Fantasia), size: (S|M|L|XL)\n"
#define TICKET_REQUEST_ASSIGNMENT_REGEX "\\[" UUID_REGEX "-" UUID_REGEX "\\] Kitchen " UUID_REGEX " requested ticket assignment\n"
#define TICKET_ASSIGNED_REGEX "\\[" UUID_REGEX "-" UUID_REGEX "\\] Ticket assigned to kitchen " UUID_REGEX "\n"
#define TICKET_MARKED_AS_DONE_REGEX "\\[" UUID_REGEX "-" UUID_REGEX "\\] Ticket marked as done\n"


typedef std::function<void(const Ticket &ticket, const std::string& message)> TicketCallback;

enum MessageType {
    NEW_TICKET,
    TICKET_REQUEST_ASSIGNMENT,
    TICKET_ASSIGNED,
    TICKET_MARKED_AS_DONE
};

extern const std::unordered_map<MessageType, std::pair<std::string, std::string>> MESSAGE_TYPE_TO_STRING;

class AbstractTicketBoard {
public:
    enum Role {
        MASTER,
        SLAVE
    };
    enum TicketEventType {
        ADDED,
        REQUESTED_ASSIGNMENT,
        ASSIGNED,
        MARKED_AS_DONE
    };

    static const std::unordered_map<MessageType, TicketEventType> RELATION_MAP;
protected:
    std::vector<Ticket> _tickets;
    std::unordered_map<TicketEventType, std::vector<TicketCallback>> _callbacks;
    bool _isRunning = false;
    Role _role;
    int _socket{};

    explicit AbstractTicketBoard(Role role);
public:
    virtual ~AbstractTicketBoard();

    virtual void run() = 0;
    virtual void stop();

    void addListener(const TicketCallback &callback, TicketEventType type);
    void addTicket(const Ticket &ticket);
    void removeTicket(const UUID &ticketUUID);
    [[nodiscard]] int getSocket() const;

    [[nodiscard]] const std::vector<Ticket> &getTickets() const;

    virtual void addCommand(const Command &command);
    virtual void removeAllTicketOfCommand(const Command &command);

    virtual void markTicketAsDone(const UUID &ticketUUID);
    virtual void markTicketAsBeingProcessed(const UUID &ticketUUID);

    class TicketBoardException : public std::exception {
    protected:
        std::string _message;
    public:
        explicit TicketBoardException(std::string message);
        ~TicketBoardException() override = default;

        [[nodiscard]] const char *what() const noexcept override;
    };

    class TicketBoardUnsupportedEventTypeException : public TicketBoardException {
    public:
        explicit TicketBoardUnsupportedEventTypeException(TicketEventType type);
        ~TicketBoardUnsupportedEventTypeException() override = default;
    };

    class TicketBoardTicketNotFoundException : public TicketBoardException {
    public:
        explicit TicketBoardTicketNotFoundException(const UUID &ticketUUID);
        ~TicketBoardTicketNotFoundException() override = default;
    };
};
