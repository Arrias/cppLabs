#include <iostream>
#include <cstring>
#include "my_vector.h"
#include <cassert>

namespace product {
    class Product {
    public:
        Product(const char *name, int quantity, double price);

        friend std::ostream &operator<<(std::ostream &out, const Product &a);

        ~Product();

        Product(const Product &other);

    private:
        char *name_{};
        int quantity_;
        double price_;
    };

    Product::Product(const char *name, int quantity, double price) : quantity_(quantity), price_(price) {
        int length = strlen(name);
        name_ = new char[length + 1];
        std::copy(name, name + length + 1, name_);
    }

    void print(const containers::my_vector<Product> &v) {
        std::cout << v << std::endl;
    }

    std::ostream &operator<<(std::ostream &out, const Product &a) {
        out << a.name_ << " " << a.quantity_ << " " << a.price_;
        return out;
    }

    Product::~Product() {
        delete[] name_;
    }

    Product::Product(const Product &other) {
        delete[] name_;
        quantity_ = other.quantity_;
        price_ = other.price_;
        int length = strlen(other.name_);
        name_ = new char[length + 1];
        std::copy(other.name_, other.name_ + length + 1, name_);
    }
}

template<typename T>
void test_my_vector_default_constructible(my_vector<T> vec) {
    std::size_t n = vec.size();
    vec.resize(n + 5);
    assert(vec.size() == n + 5);
    for (std::size_t i = 0; i < n + 4; ++i)
        vec.pop_back();
    assert(vec.size() == 1);
    my_vector<T> vec2(vec);
    vec2.reserve(150);
    assert(vec2.capacity() == 256);
    auto vec3 = vec2;
    vec3.resize(14);
    assert(vec3.size() == 14);
    assert(vec2.size() == 1);
    vec.pop_back();
    assert(vec.empty());
    vec.push_back(T());
    vec.push_back(T());
    assert(vec.size() == 2);
    vec.clear();
    assert(vec.empty());
}

template<typename T>
void test_my_vector(my_vector<T> vec) {
    std::size_t n = vec.size();
    if (n > 0) {
        vec.pop_back();
        assert(vec.size() == n - 1);
    }
    my_vector<T> vec2(vec);
    for (std::size_t i = 0; i < n - 1; ++i) {
        vec2.pop_back();
    }
    assert(vec2.empty());
    my_vector<T> vec3 = vec2;
    assert(vec3.capacity() == vec2.capacity());
    vec3.reserve(n * 2);
    assert(vec3.capacity() == n * 2);
    assert(vec3.size() == vec2.size());
}

using namespace product;

int main() {
    my_vector<Product> test1;
    test1.push_back(Product("asdf", 4, 12.0));
    test1.push_back(Product("kek", -1, 7.5));

    test_my_vector<Product>(test1);

    my_vector<int> test2;
    for (int i = 0; i < 15; ++i)
        test2.push_back(i);
    test_my_vector_default_constructible<int>(test2);
    std::cout << "Test passed...\n";

    my_vector<int> a(5);
    a[0] = 1;
    a[1] = 14;
    a[2] = 155;
    a[3] = 239;
    a[4] = 18;
    a.resize(15);
    std::cout << a << "\n";

    my_vector<int> vec(10);
    assert(vec.capacity() == 16);

    my_vector<int> kek;
    kek.reserve(20);
    assert(kek.capacity() == 32);

    auto vec44 = vec;
    vec44.resize(150);
    std::cout << vec44 << "\n";
    std::cout << vec << "\n";
    return 0;
}