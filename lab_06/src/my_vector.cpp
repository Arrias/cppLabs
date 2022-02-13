#include "my_vector.h"

const int BASE_CP = 2;
const int BASE_SZ = 0;

void MyVector::init(std::size_t new_sz, std::size_t new_cp, const int *thread) {
    _sz = new_sz;
    _cp = new_cp;

    if (_data != nullptr) {
        free(_data);
    }
    _data = (int *) calloc(_cp, sizeof(int));
    if (thread != nullptr) {
        memcpy(_data, thread, sizeof(int) * _sz);
    }
}

MyVector::MyVector() : _data(nullptr) {
    init(BASE_SZ, BASE_CP);
}

MyVector::MyVector(std::size_t init_capacity) : _data(nullptr) {
    init(BASE_SZ, init_capacity);
}

MyVector::~MyVector() {
    free(_data);
    _data = nullptr;
}

void MyVector::set(std::size_t index, int value) {
    assert(index < _sz && "index at set(...) greater than size - 1");
    _data[index] = value;
}

int MyVector::get(std::size_t index) {
    assert(index < _sz && "index at get(...) greater than size - 1");
    return _data[index];
}

std::size_t MyVector::size() const {
    return _sz;
}

std::size_t MyVector::capacity() const {
    return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
    if (new_capacity < _cp)
        return;
    _data = (int *) realloc(_data, sizeof(int) * new_capacity);
    _cp = new_capacity;
}

void MyVector::resize(std::size_t new_size) {
    if (new_size > _cp) {
        reserve(std::max(new_size, 2 * _cp));
    }
    if (new_size > _sz) {
        memset(_data + _sz, 0, sizeof(int) * (new_size - _sz));
    }
    _sz = new_size;
}

void MyVector::push_back(int value) {
    if (_sz == _cp) {
        reserve(2 * _cp);
    }
    _data[_sz++] = value;
}

void MyVector::insert(std::size_t index, int value) {
    assert(index <= _sz && "index in insert() greater than size");
    if (_sz == _cp) {
        reserve(2 * _cp);
    }
    memmove(_data + index + 1, _data + index, sizeof(int) * (_sz - index));
    _data[index] = value;
    _sz++;
}

void MyVector::erase(std::size_t index) {
    assert(index < _sz && "index in erse() greater than size - 1");
    memmove(_data + index, _data + index + 1, sizeof(int) * (_sz - index));
    _sz--;
}

MyVector::MyVector(const MyVector &vec) : _data(nullptr) {
    init(vec.size(), vec.capacity(), vec._data);
}

MyVector &MyVector::operator=(const MyVector &vec) {
    if (&vec == this) {
        return *this;
    }
    init(vec.size(), vec.capacity(), vec._data);
    return *this;
}