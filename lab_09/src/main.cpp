#include <cstdio>

#include "Scheme.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include <cassert>

void test2() {
    Scheme scheme(5);

    scheme.push_back_figure(new Rectangle(1, 0, 0, 2, 2));
    scheme.push_back_figure(new Rectangle(2, -2, -1, 2, 4));
    scheme.push_back_figure(new Rectangle(3, 3, 2, 4, 2));

    auto ans1 = scheme.is_inside_figure(1, -1);
    auto ans2 = scheme.is_inside_figure(2, 1);
    auto ans3 = scheme.is_inside_figure(-2, -2);
    auto ans4 = scheme.is_inside_figure(-1, 2);
    auto ans5 = scheme.is_inside_figure(100, 100);
    assert(ans1 != nullptr);
    assert(ans2 != nullptr);
    assert(ans3 != nullptr);
    assert(ans4 == nullptr);
    assert(ans5 == nullptr);
    printf("passed");
}

void test1() {
    Scheme scheme(5);

    auto circ1 = new Circle(1, 5, 5, 0, "second");
    auto circ0 = new Circle(0, 1, 1, 4, "first");

    scheme.push_back_figure(circ0);
    scheme.push_back_figure(circ1);
    scheme.push_back_figure(new Circle(2, 3, 3, 0, "third"));

    auto ans1 = scheme.is_inside_figure(5, 5);
    auto ans2 = scheme.is_inside_figure(100, 100);
    assert(ans1 != nullptr);
    assert(ans2 == nullptr);

    scheme.zoom_figure(0, 200);
    ans2 = scheme.is_inside_figure(100, 100);
    assert(ans2 == circ0);

    scheme.remove_figure(2);
    scheme.remove_figure(0);
    auto ans3 = scheme.is_inside_figure(5, 5);
    assert(ans3 == circ1);
}

int main() {
    Scheme scheme(10);

    scheme.push_back_figure(new Rectangle(1, 5, 5, 10, 10));
    scheme.push_back_figure(new Circle(2, 3, 3, 3, "very nice circle"));

    scheme.print_all_figures();
    scheme.print_all_figures();

    Figure *found = scheme.is_inside_figure(5, 5);
    if (found != nullptr) {
        found->print();
    } else {
        printf("not found\n");
    }

    scheme.zoom_figure(1, 2);
    scheme.print_all_figures();
    scheme.remove_figure(1);
    scheme.print_all_figures();

    test1();
    test2();

    return 0;
}