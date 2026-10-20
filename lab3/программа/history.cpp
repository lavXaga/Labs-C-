#include "history.hpp"
using namespace std;

History::History(int capacity)
    :capacity(capacity),count(0),data(new double[capacity]) {}
void History::add(double value) {
    if (count==capacity) {
        for (int i=1;i<count;i++) {
            data[i-1]=data[i];
        }count--;
        data[count]=value;
    }count++;
}
double History::getAverage() const {
    if (count==0) {
        return 0;
    }
        double sum=0;
        for (int i=0;i<count;i++) {
            sum += data[i];
        }return sum/count;
}
int History::getCount() const {
    return count;
}
double History::getAt(int index) const{
    return data[index];
}


History::~History() {delete [] data;}

History::History(const History& other)
:capacity(other.capacity),count(other.count),data(new double[other.capacity]) {for (int i = 0; i < count; i++) {
    data[i] = other.data[i];}
}
History& History::operator=(const History& other) {
    if (this!=&other) {
        delete[] data;
        capacity = other.capacity;
        count = other.count;
        data = new double[capacity];
        for (int i = 0; i < count; i++) {data[i]=other.data[i];}
    }return *this;
}
History::History(History&& other)
    : data(other.data), count(other.count), capacity(other.capacity) {
    other.data = nullptr;other.count = 0;other.capacity = 0;
}
History &History::operator=(History &&other) {
    if (this != &other) {
        delete[] data;
        capacity = other.capacity;
        count = other.count;
        data = other.data;
        other.data = nullptr;
        other.count = 0;
        other.capacity = 0;
    }return *this;
}
