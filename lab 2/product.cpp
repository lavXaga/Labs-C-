#include "product.hpp"

Product::Product(std::string name, Money price, int quantity)
    : name(name), price(price), quantity(quantity){
}

std::string Product::getName()const {
    return name;
}
Money Product::getPrice()const {
    return price;
}
int Product::getQuantity()const {
    return quantity;
}

Money Product::getTotal() const {
    return Money(price.getCopeks()*quantity);
}

