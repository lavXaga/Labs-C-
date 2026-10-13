#include <iostream>
#include "money.hpp"
#include "product.hpp"
#include <vector>
#include <windows.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Product bread("хлеб",Money(90,50),2);
    Product snup("спрей в нос",Money(82,90),5);
    Product milk("молоко",Money(30,70),1);
    Product tomato("томаты",Money(10,50),6);
    Product phone("телефон",Money(99,90),1);


    std::cout<<"корзина с товарами: "<<std::endl;
    Money total = Money(0,0);
    std::vector<Product> products={bread,snup,milk,tomato,phone};
    for (const Product& p : products) {
        std::cout<<p.getName()<<" - "<<p.getPrice()<<"| в корзине "<<p.getQuantity()<<"шт|"<<" общая стоимость "<<p.getTotal()<<std::endl;
        total = total + p.getTotal();
    }
    std::cout << "\nобщая стоимость товаров : " << total << "\n";
    int disPercent=23;
    Money discounted = total.withDiscount(disPercent);
    std::cout<<"размер скидки "<<disPercent<<"%"<<std::endl;
    std::cout<<"общая стоимость со скидкой "<<discounted<<std::endl;

    int rub, kop;
    std::cout << "сколько денег внесено руб коп: ";
    std::cin >> rub >> kop;
    Money paid(rub, kop);
    if (paid < discounted) {
        std::cout << "не хватает\n";
    } else {
        Money change = paid - discounted;
        std::cout << "сдача " << change << "\n";
    }
return 0;
}