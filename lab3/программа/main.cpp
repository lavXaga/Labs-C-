#include <iostream>
#include <iostream>
#include <fstream>
#include <memory>
#include <windows.h>
#include "controller.hpp"
#include "sensor.hpp"
using namespace std;


void processByValue(History h) {
    cout << "среднее по значению: " << h.getAverage() << "\n";}
void processByReference(History& h) {
    cout << "срелнее по ссылке: " << h.getAverage() << "\n";}
int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    auto airProfile = make_shared<Profile>("AirTempT100", -0.4, 1.02);
    auto humProfile = make_shared<Profile>("HumidityH200", 1.5, 0.98);
    auto lightProfile = make_shared<Profile>("LightLX300", 0.0, 1.10);
    Profile* emptyProfile = nullptr;
    if (emptyProfile != nullptr) {}

    Controller controller;
    controller.registerProfile(airProfile);
    controller.registerProfile(humProfile);
    controller.registerProfile(lightProfile);

    controller.addSensor(make_unique<Sensor>("TEMP_AIR_01", "temperature", "AirTempT100", 8, airProfile.get()));
    controller.addSensor(make_unique<Sensor>("TEMP_AIR_02", "temperature", "AirTempT100", 8, airProfile.get()));
    controller.addSensor(make_unique<Sensor>("HUM_AIR_01", "humidity", "HumidityH200", 10, humProfile.get()));
    controller.addSensor(make_unique<Sensor>("LIGHT_EAST_01", "light", "LightLX300", 12, lightProfile.get()));
    controller.addSensor(make_unique<Sensor>("LIGHT_WEST_01", "light", "LightLX300", 12, lightProfile.get()));



    string fileNames[5] = {
        "temp_air_01.txt",
        "temp_air_02.txt",
        "humidity_air_01.txt",
        "light_east_01.txt",
        "light_west_01.txt"
    };

    for (int i = 0; i < 5; i++) {
        ifstream in(fileNames[i]);
        if (in.is_open()) {
            double value;
            while (in >> value) {
                controller.getSensor(i)->addRawValue(value);
            }
            in.close();
        }
    }

    History histCopy = controller.getSensor(0)->getHistory();
    History histMoved = move(histCopy);


    processByValue(histMoved);
    processByReference(histMoved);


    for (size_t i = 0; i < controller.getSensorCount(); i++) {
        Sensor* s = controller.getSensor(i);

        cout << "\n ID: " << s->getId() << " |Тип: " << s->getType() << "\n";

        Profile* p = s->getProfile();
        if (p != nullptr) {
            cout << "  Профиль: " << p->getModel()
            << " (смещение: " << p->getOffset()
            << ", масштаб: " << p->getScale() << ")\n";
        }
        cout << "  Среднее значение: " << s->getHistory().getAverage() << "\n";
        cout << "  История: ";
        for (int j = 0; j < s->getHistory().getCount(); j++) {
            cout << s->getHistory().getAt(j) << " ";
        }
    }
    cout << "\n \n Всего датчиков: " << controller.getSensorCount() << "\n";
return 0;
}
