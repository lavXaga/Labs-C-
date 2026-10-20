#include "controller.hpp"

using namespace std;

void Controller::addSensor(unique_ptr<Sensor> sensor) {sensors.push_back(move(sensor));}
void Controller::registerProfile(shared_ptr<Profile> profile) {profileCatalog.push_back(profile);}

shared_ptr<Profile> Controller::findProfile(const string &model) const {
    for (size_t i = 0; i < profileCatalog.size(); i++) {
        shared_ptr<Profile> ptr = profileCatalog[i].lock();
        if (ptr) {
            if (ptr->getModel() == model) {
                return ptr;
            }
        }
    }return nullptr;
}
size_t Controller::getSensorCount() const {
    return sensors.size();
}
Sensor* Controller::getSensor(size_t index) const {
    return sensors[index].get();
}
