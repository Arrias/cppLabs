#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <ostream>

namespace containers {
    template<typename T>
    class my_vector {
    public:
        my_vector();

        explicit my_vector(std::size_t n);

        my_vector(my_vector const &other);

        my_vector<T> &operator=(my_vector<T> other);

        ~my_vector();

        std::size_t size() const;

        std::size_t capacity() const;

        bool empty() const;

        void resize(std::size_t n);

        void reserve(std::size_t n);

        T &operator[](std::size_t index) const;

        void push_back(T t);

        void pop_back();

        void clear();

    private:
        void free();

        void init(std::size_t sz, std::size_t cp, const char *elements = nullptr);

        void fill_base(std::size_t begin, std::size_t cnt);

        size_t capacity_{};
        size_t size_{};
        char *array_{};
    };
}

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_