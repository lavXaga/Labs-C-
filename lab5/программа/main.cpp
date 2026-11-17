#include "Transport.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <windows.h>
int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    std::ifstream in("parking_log.txt");
    if (!in) {
        std::cerr << "Не удалось открыть файл \n";
        return 1;
    }

    std::vector<ParkingSession> sessions;   // одна коллекция для всех типов
    std::string line;

    // --- Чтение журнала ---
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string event, timeStr, plate;
        iss >> event >> timeStr >> plate;

        if (event == "ENTER") {
            std::string type, zone;
            iss >> type >> zone;

            std::unique_ptr<Transport> t;
            if (type == "CAR")             t = std::make_unique<Car>();
            else if (type == "MOTORCYCLE") t = std::make_unique<Motorcycle>();
            else if (type == "MINIBUS")    t = std::make_unique<Minibus>();
            else if (type == "TRUCK") {
                double tons; iss >> tons;
                t = std::make_unique<Truck>(tons);
            }

            ParkingSession s;
            s.plate = plate;
            s.transport = std::move(t);
            s.zone = zone;
            s.enterMin = parseTime(timeStr);
            s.exitMin = -1;
            sessions.push_back(std::move(s));
        }
        else if (event == "EXIT") {
            // закрываем последнюю открытую сессию с этим номером
            for (auto it = sessions.rbegin(); it != sessions.rend(); ++it) {
                if (it->plate == plate && it->exitMin < 0) {
                    it->exitMin = parseTime(timeStr);
                    break;
                }
            }
        }
    }

    // --- Отчёт ---
    double revenue = 0;      // общая выручка
    int totalPlaces = 0;     // сумма мест по допустимым сессиям
    int invalid = 0;         // число недопустимых сессий

    std::cout << std::left << std::setw(9) << "Номер       "
              << std::setw(12) << "Тип  "
              << std::setw(6)  << "Зона "
              << std::setw(10) << "Минуты  "
              << std::setw(8)  << " Часы     "
              << std::setw(8)  << " Мест"
              << "    Стоимость/Ошибка\n";
    std::cout << std::string(70, '-') << "\n";

    for (const auto& s : sessions) {
        const Transport& t = *s.transport;   // вызов через ссылку на базовый тип
        int minutes = s.exitMin - s.enterMin;
        int hours = (minutes + 59) / 60;      // неполный час = полный
        if (hours < 1) hours = 1;             // минимум 1 час

        std::cout << std::left << std::setw(9) << s.plate
                  << std::setw(12) << t.code()
                  << std::setw(6)  << s.zone
                  << std::setw(10) << minutes
                  << std::setw(8)  << hours
                  << std::setw(8)  << t.places();

        if (t.zoneAllowed(s.zone)) {
            double cost = t.hourlyRate(s.zone) * hours;
            std::cout << std::fixed << std::setprecision(2) << cost << " руб.\n";
            revenue += cost;
            totalPlaces += t.places();
        } else {
            std::cout << "ОШИБКА: " << t.zoneError(s.zone) << "\n";
            ++invalid;
        }
    }

    std::cout << std::string(70, '-') << "\n";
    std::cout << "Общая выручка:       " << std::fixed << std::setprecision(2) << revenue << " руб.\n";
    std::cout << "Сумма мест:          " << totalPlaces << "\n";
    std::cout << "Недопустимых сессий: " << invalid << "\n";
    return 0;
}