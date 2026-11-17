#pragma once
#include <memory>
#include <string>

class Transport {
public:
    virtual ~Transport() = default;

    virtual std::string code() const = 0;                              // код типа
    virtual int places() const = 0;                                    // число мест
    virtual bool zoneAllowed(const std::string& zone) const = 0;       // проверка зоны
    virtual double hourlyRate(const std::string& zone) const = 0;      // рублей за час
    virtual std::string zoneError(const std::string& zone) const = 0;  // причина ошибки
};

class Car : public Transport {
public:
    std::string code() const override { return "CAR"; }
    int places() const override { return 1; }
    bool zoneAllowed(const std::string& z) const override { return z == "A" || z == "B"; }
    double hourlyRate(const std::string&) const override { return 120; }
    std::string zoneError(const std::string& z) const override {
        return "зона " + z + " недоступна для автомобиля (только A, B)";
    }
};

class Motorcycle : public Transport {
public:
    std::string code() const override { return "MOTORCYCLE"; }
    int places() const override { return 1; }
    bool zoneAllowed(const std::string& z) const override { return z == "A" || z == "B"; }
    double hourlyRate(const std::string&) const override { return 60; }
    std::string zoneError(const std::string& z) const override {
        return "зона " + z + " недоступна для мотоцикла (только A, B)";
    }
};

class Minibus : public Transport {
public:
    std::string code() const override { return "MINIBUS"; }
    int places() const override { return 2; }
    bool zoneAllowed(const std::string& z) const override { return z == "B"; }
    double hourlyRate(const std::string&) const override { return 180; }
    std::string zoneError(const std::string& z) const override {
        return "зона " + z + " недоступна для микроавтобуса (только B)";
    }
};

class Truck : public Transport {
public:
    explicit Truck(double tons) : tons_(tons) {}
    std::string code() const override { return "TRUCK"; }
    int places() const override { return 3; }
    bool zoneAllowed(const std::string& z) const override { return z == "C"; }
    double hourlyRate(const std::string&) const override { return 250 + 40 * tons_; }
    std::string zoneError(const std::string& z) const override {
        return "зона " + z + " недоступна для грузовика (только C)";
    }
private:
    double tons_;
};

class ParkingSession {
public:
    std::string plate;                     // номерной знак
    std::unique_ptr<Transport> transport;  // владение через базовый тип
    std::string zone;                      // зона
    int enterMin;                          // время въезда в минутах
    int exitMin;                           // время выезда в минутах
};

int parseTime(const std::string& s);