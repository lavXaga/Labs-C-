#include "money.hpp"

Money::Money(int rubles, int cop)
    :copeiks(rubles*100+cop){
}
Money::Money(long long cop)
    :copeiks(cop) {
}


long long Money::getCopeks() const {
    return copeiks;
}
int Money::getRubles() const {
    return copeiks/100;
}
int Money::getCopPart() const {
    return copeiks%100;

}


Money Money::operator+(const Money& other) const {
    return Money(copeiks+other.copeiks);
}
Money Money::operator-(const Money& other) const {
    return Money(copeiks-other.copeiks);
}

bool Money::operator==(const Money& other) const {
    return copeiks == other.copeiks;
}
bool Money::operator<(const Money& other) const {
    return copeiks < other.copeiks;
}
std::ostream &operator<<(std::ostream &os, const Money& m) {
    return os << m.getRubles() << "руб " << m.getCopPart() <<"коп";
}

Money Money::withDiscount(int percent) const {
    return Money((copeiks*(100-percent)+50)/100);
}
