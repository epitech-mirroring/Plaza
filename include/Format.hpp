/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <string>
#include <vector>

class Format {
    public:
        Format();
        ~Format();
        static std::string formatString(std::string str, ...);
        static std::vector<std::string> split(const std::string &str, char delim);
    private:
};
