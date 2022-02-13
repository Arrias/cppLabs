#include "matrix.h"

void Matrix::init(std::size_t r, std::size_t c, int **dt) {
    _rows = r;
    _cols = c;

    if (_data != nullptr) {
        delete[] _data[0];
        delete[] _data;
    }

    int *space = new int[_rows * _cols];
    _data = new int *[_rows];
    for (std::size_t i = 0; i < r; ++i) {
        _data[i] = space + i * _cols;
    }

    if (dt != nullptr) {
        std::copy(dt[0], dt[0] + r * c, _data[0]);
    } else {
        std::fill(_data[0], _data[0] + _rows * _cols, 0);
    }
}

Matrix::Matrix(const Matrix &m) {
    init(m._rows, m._cols, m._data);
}

Matrix::Matrix(std::size_t r, std::size_t c) {
    init(r, c);
}

Matrix &Matrix::operator=(const Matrix &m) {
    if (&m == this) {
        return *this;
    }
    init(m._rows, m._cols, m._data);
    return *this;
}

Matrix::~Matrix() {
    delete[] _data[0];
    delete[] _data;
}

std::size_t Matrix::get_rows() const {
    return _rows;
}

std::size_t Matrix::get_cols() const {
    return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    return _data[i][j];
}

void Matrix::print(FILE *f) const {
    for (std::size_t i = 0; i < _rows; ++i) {
        for (std::size_t j = 0; j < _cols; ++j) {
            fprintf(f, "%d%c", _data[i][j], " \n"[j == _cols - 1]);
        }
    }
}

bool Matrix::operator==(const Matrix &m) const {
    if (_rows != m.get_rows() || _cols != m.get_cols())
        return false;

    return std::equal(_data[0], _data[0] + _rows * _cols, m._data[0], m._data[0] + m.get_rows() * m.get_cols());
}

bool Matrix::operator!=(const Matrix &m) const {
    return !(*this == m);
}

Matrix &Matrix::operator+=(const Matrix &m) {
    *this = *this + m;
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &m) {
    *this = *this - m;
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &m) {
    *this = *this * m;
    return *this;
}

Matrix Matrix::operator+(const Matrix &m) const {
    Matrix result(_rows, _cols);

    for (std::size_t i = 0; i < _rows; ++i) {
        for (std::size_t j = 0; j < _cols; ++j) {
            result._data[i][j] = _data[i][j] + m._data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &m) const {
    Matrix result(_rows, _cols);

    for (std::size_t i = 0; i < _rows; ++i) {
        for (std::size_t j = 0; j < _cols; ++j) {
            result._data[i][j] = _data[i][j] - m._data[i][j];
        }
    }
    return result;
}


Matrix Matrix::operator*(const Matrix &m) const {
    Matrix result(_rows, m.get_cols());

    for (std::size_t i = 0; i < _rows; ++i) {
        for (std::size_t j = 0; j < m.get_cols(); ++j) {
            for (std::size_t k = 0; k < _cols; ++k) {
                result._data[i][j] += _data[i][k] * m._data[k][j];
            }
        }
    }

    return result;
}