/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <uuid/uuid.h>
#include <string>

#ifndef _UUID_STRING_T
    #define _UUID_STRING_T
typedef char uuid_string_t[37];
#endif

class UUID {
protected:
    uuid_t _uuid{};
public:
    UUID();
    explicit UUID(const uuid_t &uuid);
    UUID(const UUID &other);
    ~UUID() = default;

    [[nodiscard]] const uuid_t &getNative() const;
    void setNative(const uuid_t &uuid);
    [[nodiscard]] std::string toString(bool lowercase = true) const;
    void fromString(const std::string &string);
    bool operator==(const UUID &other) const;
    bool operator!=(const UUID &other) const;
    friend std::ostream &operator<<(std::ostream &os, const UUID &uuid);
    UUID &operator=(const UUID &other);
};
