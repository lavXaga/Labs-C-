#include "temperatur.hpp"

std::ostream& operator<<(std::ostream& os, const Celsius& t) {
    os << t.value() << " C";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Fahrenheit& t) {
    os << t.value() << " F";
    return os;
}

Fahrenheit toFahrenheit(const Celsius& c) {
    return Fahrenheit(c.value() * 9.0 / 5.0 + 32.0);
}

Celsius toCelsius(const Fahrenheit& f) {
    return Celsius((f.value() - 32.0) * 5.0 / 9.0);
}