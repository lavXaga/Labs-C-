#pragma once
#include <iostream>

class Celsius {
    double value_;
public:
    explicit Celsius(double value = 0.0) : value_(value) {}
    double value() const { return value_; }
};

class Fahrenheit {
    double value_;
public:
    explicit Fahrenheit(double value = 0.0) : value_(value) {}
    double value() const { return value_; }
};

std::ostream& operator<<(std::ostream& os, const Celsius& t);
std::ostream& operator<<(std::ostream& os, const Fahrenheit& t);

Fahrenheit toFahrenheit(const Celsius& c);
Celsius    toCelsius(const Fahrenheit& f);