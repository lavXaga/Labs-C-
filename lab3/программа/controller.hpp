#pragma once
#include <memory>
#include <vector>
#include <string>
#include "sensor.hpp"
#include "profile.hpp"

using namespace std;


class Controller {
    private:
    vector<unique_ptr<Sensor>> sensors;
    vector<weak_ptr<Profile>> profileCatalog;
    public:
    void addSensor(unique_ptr<Sensor> sensor);
    void registerProfile(shared_ptr<Profile> profile);
    shared_ptr<Profile> findProfile(const string& model) const;
    size_t getSensorCount() const;
    Sensor* getSensor(size_t index) const;
};