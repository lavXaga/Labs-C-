#pragma once
#include "profile.hpp"
#include <string>
using namespace std;

class History {
    private:
    double* data;
    int count;
    int capacity;
    public:
    History(int capacity);
    void add(double value);
    double getAverage() const;
    int getCount() const;
    double getAt(int index) const;
    ~History();
    History(History&& other);
    History(const History& other);
    History& operator=(History&& other);
    History& operator=(const History& other);
};