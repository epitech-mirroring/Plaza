/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <iostream>
#include <regex>
#include "Reception.hpp"

Reception::Reception()
{
    _isRunning = false;
    _awaitingCommands = std::vector<Command>();
    _ticketBoard = MasterTicketBoard();
}

Reception::~Reception()
{
}

void Reception::parseCommand(const std::string &command) {
    // Split the command into tokens using ';' as delimiter
    std::vector<std::string> tokens;
    std::regex re(";");
    std::sregex_token_iterator it(command.begin(), command.end(), re, -1);
    std::sregex_token_iterator reg_end;
    for (; it != reg_end; ++it) {
        tokens.push_back(*it);
    }

    Command newCommand;
    for (const auto &token : tokens) {
        std::regex pizzaRegex(" *(regina|fantasia|margarita|americana) (S|M|L|XL|XXL) x([0-9]+)");
        std::smatch match;

        if (std::regex_match(token, match, pizzaRegex)) {
            Pizza::Type type = Pizza::parseType(match[1]);
            Pizza::Size size = Pizza::parseSize(match[2]);
            int quantity = std::stoi(match[3]);
            for (int i = 0; i < quantity; i++) {
                newCommand.addPizza(Pizza(type, size));
            }
        } else {
            std::cerr << "Invalid pizza: " << token << std::endl;
            std::cerr << "This pizza will be skipped in your final order" << std::endl;
        }
    }
    _awaitingCommands.push_back(newCommand);
    _ticketBoard.addCommand(newCommand);
    std::cout << "New command added to the queue" << std::endl;
    std::cout << newCommand << std::endl;
}

void Reception::run()
{
    _isRunning = true;
    _ticketBoard.run();
    fd_set readfds;
    struct timeval tv = {0, 0};
    while (_isRunning) {
        FD_ZERO(&readfds);
        FD_SET(stdin->_file, &readfds);
        select(stdin->_file + 1, &readfds, nullptr, nullptr, &tv);
        // If ctrl+d is pressed we stop the reception
        if (std::cin.eof()) {
            _isRunning = false;
            continue;
        }
        if (FD_ISSET(stdin->_file, &readfds)) {
            std::string command;
            std::getline(std::cin, command);
            if (command.empty())
                continue;
            parseCommand(command);
        }
    }
    _ticketBoard.stop();
    _ticketBoard->join();
}
