#include <cstdio>
#include <cstdlib>

#include "my_vector.h"
#include <iostream>

void print(MyVector& a) {
    for (int i = 0; i < a.size(); ++i)
        std::cout << a.get(i) << " ";
    std::cout << "\n";
}

void kek(MyVector a) {
    a.set(0, 150);
    print(a);
}

int main(int argc, char **argv) {
    MyVector a(10);
    a.push_back(3);
    a.push_back(4);
    MyVector b(a);

    print(b);

    return 0;
}