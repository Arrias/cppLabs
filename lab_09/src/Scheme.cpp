#include "Scheme.hpp"
#include <cassert>
#include <cstring>

Scheme::Scheme(int capacity) : cp(capacity) {
    figures_ = new Figure *[capacity];
}

Scheme::~Scheme() {
    for (int i = 0; i < size; ++i) {
        delete figures_[i];
    }
    delete[] figures_;
    figures_ = nullptr;
}

int Scheme::findFigureById(int id) const {
    int pos = 0;
    while (pos < size && figures_[pos]->getId() != id) {
        pos++;
    }
    return pos;
}

void Scheme::move(int id, int new_x, int new_y) {
    id = findFigureById(id);
    assert(id < size && "this id doesn't exist");
    figures_[id]->move(new_x, new_y);
}

Figure *Scheme::is_inside_figure(int x, int y) {
    for (int i = 0; i < size; ++i) {
        if (figures_[i]->is_inside(x, y)) {
            return figures_[i];
        }
    }
    return nullptr;
}

void Scheme::print_all_figures() {
    for (int i = 0; i < size; ++i) {
        figures_[i]->print();
    }
}

void Scheme::remove_figure(int id) {
    id = findFigureById(id);
    assert(id < size && "this id doesn't exist");
    delete figures_[id];
    std::memmove(figures_ + id, figures_ + id + 1, sizeof(Figure *) * (size - id - 1));
    size--;
}

void Scheme::push_back_figure(Figure *fg) {
    assert(size < cp && "Scheme size exceeded");
    figures_[size++] = fg;
}

void Scheme::zoom_figure(int id, int factor) {
    id = findFigureById(id);
    assert(id < size && "this id doesn't exist");
    figures_[id]->zoom(factor);
}