#include"sensor.hpp"
using namespace std;


Sensor::Sensor(string id, string type, string model, int historyCapacity, Profile *profile)
    : id(id), type(type), model(model), history(historyCapacity), profile(profile){
}

void Sensor::addRawValue(double raw) {
    if (profile != nullptr) {
        history.add(profile->calibrate(raw));
    }
}

string Sensor::getId() const {
    return id;
}
string Sensor::getType() const {
    return type;
}
string Sensor::getModel() const {
    return model;
}
const History &Sensor::getHistory() const {
    return history;
}
Profile *Sensor::getProfile() const {
    return profile;
}
