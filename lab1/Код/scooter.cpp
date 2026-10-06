#include "scooter.hpp"

#include <bemapiset.h>

hp getState(bool fault, double mileage, int charge ) {
    if (fault) {
        return hp::SERVICE_REQUIRED;
    }else if (mileage >= MILEAGE ) {
        return hp::SERVICE_REQUIRED;
    }else if (charge < CHARGE ) {
        return hp::CHARGE_REQUIRED;
    }else {
        return hp::READY;
    }
}

bool readScooter( std::istream& in, Scooter& s) {
    if (in >> s.num >> s.model >> s.charge >> s.mileage >> s.fault ) {
        s.status = getState( s.fault, s.mileage, s.charge );
        return true;
    }else {
        return false;
    }
}
void writeScooter( std::ostream& out, const Scooter& s ) {
    out << s.num <<' '<< s.model <<' '<< s.charge <<' '<< s.mileage <<' '<< s.fault<<'\n';
}
