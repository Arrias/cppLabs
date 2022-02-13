#ifndef LAB_13_MY_ARRAY_H
#define LAB_13_MY_ARRAY_H

#include <cassert>
#include <algorithm>

const uint8_t BITS = 1 << 3;

namespace lab_13 {
    template<typename T, std::size_t N>
    class my_array {
    public:
        const T &at(std::size_t index) const {
            assert(index < N && "index greater than n - 1");
            return operator[](index);
        }

        T &at(std::size_t index) {
            assert(index < N && "index greater than n - 1");
            return operator[](index);
        }

        my_array() {}

        my_array(const my_array<T, N> &other) {
            std::copy(other.ar, other.ar + N, ar);
        }

        my_array operator=(my_array<T, N> other) {
            std::swap(ar, other.ar);
        }

        T &operator[](std::size_t index) {
            return ar[index];
        }

        const T &operator[](std::size_t index) const {
            return ar[index];
        }

        bool empty() const {
            return size() == 0;
        }

        std::size_t size() const {
            return N;
        }

        void fill(const T &val) {
            std::fill(ar, ar + N, val);
        }

    private:
        T ar[N]{};
    };

    template<std::size_t N>
    class my_array<bool, N> {
    private:
        class proxy;

        uint8_t ar[(N + BITS - 1) / BITS]{};
    public:

        bool empty() const {
            return size() == 0;
        }

        std::size_t size() const {
            return N;
        }

        proxy operator[](std::size_t index) {
            return proxy(ar[index / BITS], index % BITS);
        }

        const proxy operator[](std::size_t index) const {
            return proxy(ar[index / BITS], index % BITS);
        }

        proxy at(std::size_t index) {
            assert(index < N && "index greater than n - 1");
            return operator[](index);
        }

        const proxy at(std::size_t index) const {
            assert(index < N && "index greater than n - 1");
            return operator[](index);
        }

        void fill(bool value) {
            std::fill(ar, ar + (N + BITS - 1) / BITS, (value ? UINT8_MAX : 0));
        }

    private:
        class proxy {
        public:
            operator bool() const {
                return (mem >> num) & 1;
            }

            proxy operator=(bool value) {
                if (!value) {
                    mem &= ~(1 << num);
                } else {
                    mem |= (1 << num);
                }
                return *this;
            }

            proxy operator=(proxy &other) {
                return *this = (bool) other;
            }

        private:
            uint8_t &mem;
            uint8_t num;

            proxy(const uint8_t &mem_, const uint8_t num_) : mem(const_cast<uint8_t &>(mem_)), num(num_) {}

            friend class my_array;
        };
    };
}


#endif //LAB_13_MY_ARRAY_H
