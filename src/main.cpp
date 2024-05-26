/*
** EPITECH PROJECT, 2024
** Plaza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <chrono>
#include "Reception.hpp"
#include "Kitchen.hpp"

int main(int ac, char **av) {
    if (ac != 4)
        return 84;
    float multiplier = std::stof(av[1]);
    int nb_cooks = std::stoi(av[2]);
    long time = std::stol(av[3]);

    if (multiplier <= 0 || nb_cooks <= 0 || time <= 0)
        return 84;

    Reception reception(multiplier, nb_cooks, time);
    reception.run();
    return 0;
}
