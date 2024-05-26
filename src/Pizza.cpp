/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Pizza.hpp"

Pizza::Pizza(Pizza::Type type, Pizza::Size size) {
    this->_type = type;
    this->_size = size;
}

Pizza::~Pizza() = default;

Pizza::Type Pizza::getType() const {
    return this->_type;
}

Pizza::Size Pizza::getSize() const {
    return this->_size;
}

void Pizza::setType(Pizza::Type type) {
    this->_type = type;
}

void Pizza::setSize(Pizza::Size size) {
    this->_size = size;
}

bool Pizza::operator==(const Pizza &other) const {
    return this->_type == other._type && this->_size == other._size;
}

bool Pizza::operator!=(const Pizza &other) const {
    return !(*this == other);
}

std::ostream &operator<<(std::ostream &os, const Pizza &pizza) {
    os << pizza.getType() << " " << pizza.getSize();
    return os;
}

std::ostream &operator<<(std::ostream &os, const Pizza::Type &type) {
    switch (type) {
        case Pizza::Type::Regina:
            os << "Regina";
            break;
        case Pizza::Type::Margarita:
            os << "Margarita";
            break;
        case Pizza::Type::Americana:
            os << "Americana";
            break;
        case Pizza::Type::Fantasia:
            os << "Fantasia";
            break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Pizza::Size &size) {
    switch (size) {
        case Pizza::Size::S:
            os << "S";
            break;
        case Pizza::Size::M:
            os << "M";
            break;
        case Pizza::Size::L:
            os << "L";
            break;
        case Pizza::Size::XL:
            os << "XL";
            break;
        case Pizza::Size::XXL:
            os << "XXL";
            break;
    }
    return os;
}

static std::string lowercase(const std::string &str) {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
}

Pizza::Type Pizza::parseType(const std::string &type) {
    if (lowercase(type) == "regina")
        return Pizza::Type::Regina;
    if (lowercase(type) == "margarita")
        return Pizza::Type::Margarita;
    if (lowercase(type) == "americana")
        return Pizza::Type::Americana;
    if (lowercase(type) == "fantasia")
        return Pizza::Type::Fantasia;
    throw std::invalid_argument("Invalid pizza type");
}

Pizza::Size Pizza::parseSize(const std::string &size) {
    if (lowercase(size) == "s")
        return Pizza::Size::S;
    if (lowercase(size) == "m")
        return Pizza::Size::M;
    if (lowercase(size) == "l")
        return Pizza::Size::L;
    if (lowercase(size) == "xl")
        return Pizza::Size::XL;
    if (lowercase(size) == "xxl")
        return Pizza::Size::XXL;
    throw std::invalid_argument("Invalid pizza size");
}

std::string Pizza::typeToString(Pizza::Type type) {
    switch (type) {
        case Pizza::Type::Regina:
            return "Regina";
        case Pizza::Type::Margarita:
            return "Margarita";
        case Pizza::Type::Americana:
            return "Americana";
        case Pizza::Type::Fantasia:
            return "Fantasia";
    }
    return "";
}

std::string Pizza::sizeToString(Pizza::Size size) {
    switch (size) {
        case Pizza::Size::S:
            return "S";
        case Pizza::Size::M:
            return "M";
        case Pizza::Size::L:
            return "L";
        case Pizza::Size::XL:
            return "XL";
        case Pizza::Size::XXL:
            return "XXL";
    }
    return "";
}
