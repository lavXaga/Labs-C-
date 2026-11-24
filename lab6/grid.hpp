#pragma once
#include <iostream>
#include <deque>
#include <stdexcept>
#include <concepts>
#include <cstddef>
#include <optional>
#include <utility>


template <typename T>
bool inRange(const T& value, const T& lo, const T& hi) {
    return value >= lo && value <= hi;
}

template <typename T>
T clampValue(const T& value, const T& lo, const T& hi) {
    if (value < lo) return lo;
    if (value > hi) return hi;
    return value;
}


template <typename T>
concept EqualityComparable = requires(const T& a, const T& b) {
    { a == b } -> std::convertible_to<bool>;
};

template <typename T>
concept Numeric = (std::integral<T> || std::floating_point<T>) && !std::same_as<T, bool>;


template <typename T>
void printValue(std::ostream& os, const T& value) {
    os << value;
}

inline void printValue(std::ostream& os, bool value) {
    os << (value ? '#' : '.');
}



template <typename T>
class Grid {
public:
    Grid() = default;
    Grid(std::size_t width, std::size_t height, T initial = T{})
        : width_(width), height_(height), cells_(width * height, initial) {}

    std::size_t width()  const { return width_; }
    std::size_t height() const { return height_; }
    bool empty() const { return cells_.empty(); }

    bool validCoords(int x, int y) const {
        return x >= 0 && y >= 0 &&
               static_cast<std::size_t>(x) < width_ &&
               static_cast<std::size_t>(y) < height_;
    }

    T& at(int x, int y) {
        checkCoords(x, y);
        return cells_[static_cast<std::size_t>(y) * width_ + static_cast<std::size_t>(x)];
    }
    const T& at(int x, int y) const {
        checkCoords(x, y);
        return cells_[static_cast<std::size_t>(y) * width_ + static_cast<std::size_t>(x)];
    }

    void fill(const T& value) {
        for (auto& c : cells_) c = value;
    }

    template <EqualityComparable U = T>
    std::size_t count(const T& value) const {
        std::size_t n = 0;
        for (const auto& c : cells_) if (c == value) ++n;
        return n;
    }

    template <EqualityComparable U = T>
    std::optional<std::pair<int,int>> findFirst(const T& value) const {
        for (std::size_t y = 0; y < height_; ++y)
            for (std::size_t x = 0; x < width_; ++x)
                if (cells_[y * width_ + x] == value)
                    return std::make_pair(static_cast<int>(x), static_cast<int>(y));
        return std::nullopt;
    }

    template <Numeric U = T>
    T minValue() const {
        if (empty()) throw std::runtime_error("минимум на пустой карте не определён");
        T m = cells_[0];
        for (const auto& c : cells_) if (c < m) m = c;
        return m;
    }

    template <Numeric U = T>
    T maxValue() const {
        if (empty()) throw std::runtime_error("максимум на пустой карте не определён");
        T m = cells_[0];
        for (const auto& c : cells_) if (c > m) m = c;
        return m;
    }

    template <Numeric U = T>
    double average() const {
        if (empty()) throw std::runtime_error("среднее на пустой карте не определено");
        double sum = 0;
        for (const auto& c : cells_) sum += static_cast<double>(c);
        return sum / static_cast<double>(cells_.size());
    }

    template <Numeric U = T>
    void replaceBelow(const T& bound, const T& newValue) {
        for (auto& c : cells_) if (c < bound) c = newValue;
    }

    void print(std::ostream& os) const {
        for (std::size_t y = 0; y < height_; ++y) {
            for (std::size_t x = 0; x < width_; ++x) {
                printValue(os, cells_[y * width_ + x]);
                os << ' ';
            }
            os << '\n';
        }
    }

private:
    void checkCoords(int x, int y) const {
        if (!validCoords(x, y))
            throw std::out_of_range("Grid: недопустимые координаты");
    }

    std::size_t width_ = 0;
    std::size_t height_ = 0;
    std::deque<T> cells_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Grid<T>& grid) {
    grid.print(os);
    return os;
}


void printTemplateArgumentDemo();
void printExplicitArgumentDemo();