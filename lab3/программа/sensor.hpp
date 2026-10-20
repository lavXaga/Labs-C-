#pragma once
#include <string>
#include "history.hpp"
#include "profile.hpp"
using namespace std;

class Sensor {
private:
    string id;
    string type;
    string model;
    History history;
    Profile* profile;
    public:
    Sensor(string id,string type,string model,int historyCapacity, Profile* profile);
    void addRawValue(double raw);
    string getId() const;
    string getType() const;
    string getModel() const;
    const History& getHistory() const;
    Profile* getProfile() const;
};
