#include <windows.h>
#include "grid.hpp"
#include <iostream>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    constexpr std::size_t W = 8, H = 6;

    Grid<bool> obstacles(W, H, false);
    obstacles.at(0, 0) = true;
    obstacles.at(3, 2) = true;
    obstacles.at(5, 4) = true;
    obstacles.at(7, 5) = true;
    obstacles.at(1, 3) = true;
    obstacles.at(6, 1) = true;
    obstacles.at(2, 5) = true;
    obstacles.at(4, 0) = true;

    std::cout << "Карта препятствий:\n" << obstacles;
    std::cout << "количество препятствий = " << obstacles.count(true) << '\n';
    if (auto p = obstacles.findFirst(true))
        std::cout << "первое препятствие в (" << p->first << ", " << p->second << ")\n";

    Grid<double> distances(W, H, 1.0);
    distances.at(0, 1) = 3.5;
    distances.at(4, 4) = 0.0;
    std::cout << "\nКарта расстояний:\n" << distances;
    std::cout << "мин = " << distances.minValue()
              << " макс = " << distances.maxValue()
              << " среднее = " << distances.average() << '\n';

    Grid<int> cost(W, H, 1);
    cost.at(2, 2) = 9;
    cost.at(3, 3) = 5;
    std::cout << "\nКарта стоимости прохода:\n" << cost;
    std::cout << "мин = " << cost.minValue()
              << " макс = " << cost.maxValue()
              << " среднее = " << cost.average() << '\n';

    Grid<float> probability(W, H, 0.9f);
    probability.at(0, 0) = 0.1f;
    probability.at(2, 3) = 0.2f;
    probability.at(5, 5) = 0.05f;
    std::cout << "\nКарта вероятностей до:\n" << probability;
    probability.replaceBelow(0.25f, 0.25f);
    std::cout << "Карта вероятностей после replaceBelow(0.25):\n" << probability;

    std::cout << "\n";
    printTemplateArgumentDemo();
    printExplicitArgumentDemo();

    Grid<int> emptyGrid;
    std::cout << "пустая: " << std::boolalpha << emptyGrid.empty() << std::noboolalpha
              << ", размер = " << emptyGrid.width() << 'x' << emptyGrid.height() << '\n';
    try { emptyGrid.minValue(); }
    catch (const std::exception& e) { std::cout << "ожидаемая ошибка: " << e.what() << '\n'; }

    return 0;
}