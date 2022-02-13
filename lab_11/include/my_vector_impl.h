
#include "my_vector.h"

using namespace containers;

const int BASE_CP = 1;
const int BASE_SZ = 0;

template<typename T>
void my_vector<T>::init(std::size_t sz, std::size_t cp, const char *elements) {
    free();
    size_ = sz;
    capacity_ = cp;
    array_ = new char[capacity_ * sizeof(T)]{};

    if (elements != nullptr) {
        for (std::size_t i = 0; i < size_; ++i) {
            new(array_ + i * sizeof(T)) T(*(T *) (elements + i * sizeof(T)));
        }
    }
}

template<typename T>
my_vector<T>::my_vector() {
    init(BASE_SZ, BASE_CP);
}

template<typename T>
my_vector<T>::my_vector(std::size_t n) {
    std::size_t cp = 1;
    while (cp < n) {
        cp <<= 1;
    }
    init(n, cp);
    fill_base(0, n);
}

template<typename T>
my_vector<T>::my_vector(const my_vector &other) {
    init(other.size(), other.capacity(), other.array_);
}

template<typename T>
my_vector<T> &my_vector<T>::operator=(my_vector<T> other) {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(array_, other.array_);
    return *this;
}

template<typename T>
my_vector<T>::~my_vector() {
    free();
}

template<typename T>
std::size_t my_vector<T>::size() const {
    return size_;
}

template<typename T>
std::size_t my_vector<T>::capacity() const {
    return capacity_;
}

template<typename T>
bool my_vector<T>::empty() const {
    return size() == 0;
}

template<typename T>
void my_vector<T>::resize(std::size_t n) {
    if (n > capacity_) {
        reserve(n);
    }

    if (n > size_) {
        fill_base(size_, n - size_);
    } else if (n < size_) {
        while (size_ > n) {
            pop_back();
        }
    }
    size_ = n;
}

template<typename T>
void my_vector<T>::reserve(std::size_t n) {
    if (n < capacity_)
        return;

    std::size_t new_cp = capacity_;
    while (new_cp < n) {
        new_cp <<= 1;
    }
    n = new_cp;

    char *new_mem = new char[n * sizeof(T)]{};

    for (std::size_t i = 0; i < size_; ++i)
        new(new_mem + i * sizeof(T)) T(operator[](i));

    std::size_t temp_size = size_;
    free();
    array_ = new_mem;
    capacity_ = n;
    size_ = temp_size;
}

template<typename T>
T &my_vector<T>::operator[](std::size_t index) const {
    return *(T *) (array_ + index * sizeof(T));
}

template<typename T>
void my_vector<T>::push_back(T t) {
    if (size_ == capacity_) {
        reserve(2 * capacity_);
    }
    new(array_ + size_ * sizeof(T)) T(t);
    size_++;
}

template<typename T>
void my_vector<T>::pop_back() {
    ((T *) (array_ + (size_ - 1) * sizeof(T)))->~T();
    size_--;
}

template<typename T>
void my_vector<T>::clear() {
    while (size() > 0) {
        pop_back();
    }
}

template<typename T>
void my_vector<T>::fill_base(std::size_t begin, std::size_t cnt) {
    for (std::size_t i = 0; i < cnt; ++i) {
        new(array_ + (begin + i) * sizeof(T)) T();
    }
}

template<typename T>
void my_vector<T>::free() {
    if (array_ == nullptr) return;
    clear();

    delete[] array_;
    size_ = capacity_ = 0;
    array_ = nullptr;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const my_vector<T> &a) {
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (i) {
            out << " ";
        }
        out << a[i];
    }
    return out;
}


