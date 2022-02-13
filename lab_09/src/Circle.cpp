#include "Circle.hpp"
#include <cstring>
#include <algorithm>
#include <cstdio>

Circle::Circle(int id, int x, int y, int radius, const char *label) : Figure(id, x, y), r(radius) {
    int length = strlen(label);
    this->label = new char[length + 1]{};
    std::copy(label, label + length + 1, this->label);
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, r, label);
}

bool Circle::is_inside(int x, int y) const {
    return (this->x - x) * (this->x - x) + (this->y - y) * (this->y - y) <= r * r;
}

void Circle::zoom(int factor) {
    r *= factor;
}

Circle::~Circle() {
    delete[] label;
    label = nullptr;
}