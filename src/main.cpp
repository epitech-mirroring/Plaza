/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Kitchen.hpp"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    Kitchen kitchen(2, std::chrono::milliseconds(5), 2000);
    Command command;
    command.addPizza(Pizza(Pizza::Regina, Pizza::S));
    Ticket ticket(command, 0);
    kitchen.addTicket(ticket);
    kitchen.loop();
    return 0;
}
