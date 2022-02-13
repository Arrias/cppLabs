#include "Rectangle.hpp"
#include "cstdio"

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y), width(width), height(height) {}

bool Rectangle::is_inside(int x, int y) const {
    int a = this->x;
    int b = this->y;
    return (-width <= 2 * (x - a) && 2 * (x - a) <= width && -height <= 2 * (y - b) && 2 * (y - b) <= height);
}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}

void Rectangle::zoom(int factor) {
    width *= factor;
    height *= factor;
}

