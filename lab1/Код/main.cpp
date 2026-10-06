#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include "scooter.hpp"


int main(){

std::ifstream in("scooters.txt");
if (!in) {
        std::cerr << "file not open\n";
         return 1;
 }
        std::ofstream readyFile("ready.txt");
        std::ofstream chargeFile("charge_required.txt");
        std::ofstream serviceFile("service_required.txt");


        int scooterCount = 0;
        int chargeCount = 0;
        int serviceCount = 0;
        int readyCount = 0;
        double sumCharge = 0;

Scooter s;
        while (readScooter(in,s)) {
                scooterCount++;
                sumCharge += s.charge;
                if (s.status==hp::READY) {
                        writeScooter(readyFile,s);
                        readyCount++;
                }else if (s.status==hp::SERVICE_REQUIRED) {
                        writeScooter(serviceFile,s);
                        serviceCount++;
                }else if (s.status==hp::CHARGE_REQUIRED) {
                        writeScooter(chargeFile,s);
                        chargeCount++;
                }
        }
        std::cout << scooterCount << std::endl;
        std::cout << readyCount << std::endl;
        std::cout << chargeCount << std::endl;
        std::cout << serviceCount << std::endl;
        std::cout << ((double)readyCount/scooterCount)*100<<"%" << std::endl;;
        std::cout << sumCharge/scooterCount << std::endl;
return 0;
}
