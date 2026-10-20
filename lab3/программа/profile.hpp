#pragma once
#include <iostream>
#include <string>
using namespace std;

class Profile {
    private:
    string model;
    double offset;
    double scale;
    public:
    Profile(string model, double offset, double scale);
    string getModel() const;
    double getOffset() const;
    double getScale() const;
    double calibrate(double raw)const;

};


