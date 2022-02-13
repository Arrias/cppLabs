#ifndef _MY_VECTOR_H_INCLUDED
#define _MY_VECTOR_H_INCLUDED

#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <cstring>

class MyVector {
public: // methods
    MyVector();

    MyVector(const MyVector &vec);

    MyVector(std::size_t init_capacity);

    ~MyVector();

    MyVector &operator=(const MyVector &vec);

    void set(std::size_t index, int value);

    int get(std::size_t index);

    std::size_t size() const;

    std::size_t capacity() const;

    void reserve(std::size_t new_capacity);

    void resize(std::size_t new_size);

    void push_back(int value);

    void insert(std::size_t index, int value);

    void erase(std::size_t index);

private: // fields
    void init(std::size_t new_sz, std::size_t new_cp, const int *thread = nullptr);

    std::size_t _sz{}, _cp{};
    int *_data;
};

#endif