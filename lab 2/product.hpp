#pragma once
#include "money.hpp"
#include <string>

class Product {
private:
    std::string name;
    Money price;
    int quantity;
public:
    Product (std::string name, Money price, int quantity);
    std::string getName()const;
    Money getPrice()const;
    int getQuantity()const;
    Money getTotal()const;
};