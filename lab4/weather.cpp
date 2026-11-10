#include "temperatur.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <windows.h>
struct Measurement {
    std::string time;
    Celsius     temperature;
    double      humidity, pressure, wind;
};

bool readMeasurements(const std::string& filename, std::vector<Measurement>& out) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл '" << filename << "'\n";
        return false;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string t, temp, hum, pres, wind;
        std::getline(ss, t,    ',');
        std::getline(ss, temp, ',');
        std::getline(ss, hum,  ',');
        std::getline(ss, pres, ',');
        std::getline(ss, wind, ',');
        out.push_back({ t, Celsius(std::stod(temp)),
                        std::stod(hum), std::stod(pres), std::stod(wind) });
    }
    return true;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::vector<Measurement> data;
    if (!readMeasurements("weather_day.csv", data)) return 1;

    double sum = 0.0;
    for (const auto& m : data) sum += m.temperature.value();
    Celsius avg(sum / static_cast<int>(data.size()));

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Измерений: " << data.size() << "\n";
    std::cout << "Средняя температура: " << avg << "\n";

    double avgC = static_cast<double>(avg.value());
    Fahrenheit avgF = toFahrenheit(Celsius(avgC));
    std::cout << "Средняя в Фаренгейтах: " << avgF << "\n";
}