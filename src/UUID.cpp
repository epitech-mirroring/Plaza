/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "UUID.hpp"

UUID::UUID() {
    uuid_generate(this->_uuid);
}

UUID::UUID(const uuid_t &uuid) {
    uuid_copy(this->_uuid, uuid);
}

UUID::UUID(const UUID &other) {
    uuid_copy(this->_uuid, other._uuid);
}

const uuid_t &UUID::getNative() const {
    return this->_uuid;
}

void UUID::setNative(const uuid_t &uuid) {
    uuid_copy(this->_uuid, uuid);
}

std::string UUID::toString(bool lowercase) const {
    uuid_string_t str;

    if (lowercase)
        uuid_unparse_lower(this->_uuid, str);
    else
        uuid_unparse_upper(this->_uuid, str);
    return {str};
}

void UUID::fromString(const std::string &string) {
    uuid_parse(string.c_str(), this->_uuid);
}

bool UUID::operator==(const UUID &other) const {
    return uuid_compare(this->_uuid, other._uuid) == 0;
}

bool UUID::operator!=(const UUID &other) const {
    return uuid_compare(this->_uuid, other._uuid) != 0;
}

std::ostream &operator<<(std::ostream &os, const UUID &uuid) {
    return os << uuid.toString();
}

UUID &UUID::operator=(const UUID &other) {
    if (this == &other)
        return *this;
    uuid_copy(this->_uuid, other._uuid);
    return *this;
}
