#include "Transport.hpp"
#include <stdexcept>

int parseTime(const std::string& s) {
    auto p = s.find(':');
    if (p == std::string::npos)
        throw std::runtime_error("неверный формат времени: " + s);
    return std::stoi(s.substr(0, p)) * 60 + std::stoi(s.substr(p + 1));
}