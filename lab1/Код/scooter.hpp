#pragma once
#include <string>
#include <istream>

enum class hp {
    SERVICE_REQUIRED, //целый или нет + пробег
    CHARGE_REQUIRED,   //зарядка
    READY              //все норм

};

const double MILEAGE = 1500;
const int CHARGE = 30;

struct Scooter{
    std::string num;
    std::string model;
    int charge;
    double mileage;
    bool fault;
    hp status;
};

hp getState(bool fault, double mileage, int charge );
bool readScooter( std::istream& in, Scooter& s) ;
void writeScooter( std::ostream& out, const Scooter& s) ;
