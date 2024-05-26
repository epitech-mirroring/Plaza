/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <cstdarg>
#include <cstdio>
#include <iostream>
#include "Format.hpp"

Format::Format() = default;

Format::~Format() = default;

std::string Format::formatString(std::string str, ...)
{
    va_list args;
    va_start(args, str);
    char *buffer = new char[4096];
    vsnprintf(buffer, 4096, str.c_str(), args);
    va_end(args);
    std::string ret(buffer);
    delete[] buffer;
    return ret;
}

std::vector<std::string> Format::split(const std::string &str, char delim)
{
    std::vector<std::string> elems;
    std::string elem;
    for (char c : str) {
        if (c == delim) {
            elems.push_back(elem);
            elem.clear();
        } else {
            elem += c;
        }
    }
    elems.push_back(elem);
    return elems;
}
