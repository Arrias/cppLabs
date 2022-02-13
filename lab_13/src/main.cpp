#include <cstddef>
#include "my_array.h"
#include <iostream>

using lab_13::my_array;

template<typename T, std::size_t N>
void test_core() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.empty();
    ca.empty();
    a.size();
    ca.size();

    a.at(0);
    ca.at(0);
    a[0];
    ca[0];
    (void) static_cast<const T &>(a[0]);
    (void) static_cast<const T &>(ca[0]);
}

template<typename T, std::size_t N>
void test_assign() {
    my_array<T, N> a;
    const my_array<T, N> &ca = a;
    a.fill(T());
    a[0] = T();
    a[0] = a[0];
    a[0] = ca[0];
}

class NonCopyable {
public:
    NonCopyable() {}

private:
    NonCopyable(const NonCopyable &) = delete;

    NonCopyable &operator=(const NonCopyable) = delete;
};

char buf[] = "leg_gross";

class Feggie {
public:
    char *rank;

    Feggie() {
        rank = new char[15]{};
        std::copy(buf, buf + 9, rank);
    }

    Feggie(const Feggie &f) {
        rank = new char[15]{};
        std::copy(buf, buf + 9, rank);
    }

    Feggie &operator=(Feggie other) {
        std::swap(rank, other.rank);
        return *this;
    }

    ~Feggie() {
        delete[]rank;
    }
};

void test2() {
    my_array<Feggie, 150> kek;

    kek[0] = Feggie();
    kek[1] = Feggie();
    kek[2] = Feggie();
    kek[3] = Feggie();
}

int main() {
    test2();
    test_core<int, 10>();
    test_core<bool, 10>();
    test_core<NonCopyable, 10>();

    my_array<bool, 10> ar;
    ar[3] = 1;
    ar[4] = 1;
    ar.fill(0);
    for (int i = 0; i <ar.size(); ++i)
        std::cout << ar[i] << " ";

    test_assign<int, 10>();
    test_assign<bool, 10>();
}