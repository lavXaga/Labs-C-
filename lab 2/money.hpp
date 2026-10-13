#pragma once
#include <ostream>



class Money {
    private:
    long long copeiks;
    public:
    Money(int rubles,int cop);
    explicit Money(long long cop );
    long long getCopeks() const;
    int getRubles() const;
    int getCopPart() const;
    Money operator+(const Money& other)const;
    Money operator-(const Money &other)const;
    bool operator<(const Money& other)const;
    bool operator==(const Money& other)const;
    Money withDiscount(int percent)const;
};

std::ostream& operator<<(std::ostream& os, const Money& m);


