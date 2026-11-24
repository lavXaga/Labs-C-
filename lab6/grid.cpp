#include "grid.hpp"

void printTemplateArgumentDemo() {
    bool b = inRange(3, 1, 5);
    bool f = inRange(0.5f, 0.0f, 1.0f);
    std::cout << "inRange (вывод типа): "
              << std::boolalpha << b << ' ' << f << std::noboolalpha << '\n';
}

void printExplicitArgumentDemo() {
    bool d = inRange<double>(0.3, 0.0, 1.0);
    int  c = clampValue<int>(42, 0, 10);
    std::cout << "явный тип: " << std::boolalpha << d << std::noboolalpha
              << ' ' << c << '\n';
}