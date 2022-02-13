#include "matrix.h"
#include <algorithm>
#include <fstream>
#include <iostream>

void Matrix::init(std::size_t r, std::size_t c, int **dt) {
    _rows = r;
    _cols = c;

    if (_data != nullptr) {
        delete[] _data[0];
        delete[] _data;
    }

    if (!_rows && !_cols) {
        return;
    }
    int *space = new int[_rows * _cols]{};
    _data = new int *[_rows]{};
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
    if (!_rows && !_cols) {
        return;
    }

    delete[] _data[0];
    delete[] _data;
}

std::size_t Matrix::get_rows() const noexcept {
    return _rows;
}

std::size_t Matrix::get_cols() const noexcept {
    return _cols;
}

void Matrix::set(int i, int j, int val) {
    if (i < 0 || j < 0 || i >= (int) _cols || j >= (int) _rows) {
        throw MatrixException("ACCESS: bad index.");
    }
    _data[i][j] = val;
}

int Matrix::get(int i, int j) const {
    if (i < 0 || j < 0 || i >= (int) _cols || j >= (int) _rows) {
        throw MatrixException("ACCESS: bad index.");
    }
    return _data[i][j];
}

void Matrix::print() const {
    for (std::size_t i = 0; i < _rows; ++i) {
        for (std::size_t j = 0; j < _cols; ++j) {
            std::cout << _data[i][j] << " \n"[j == _cols - 1];
        }
    }
}

bool Matrix::operator==(const Matrix &m) const noexcept {
    if (_rows != m.get_rows() || _cols != m.get_cols())
        return false;

    return std::equal(_data[0], _data[0] + _rows * _cols, m._data[0], m._data[0] + m.get_rows() * m.get_cols());
}

bool Matrix::operator!=(const Matrix &m) const noexcept {
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
    if (_rows != m._rows || _cols != m._cols) {
        throw MatrixException("ADD: dimensions do not match.");
    }
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
    if (_cols != m._rows) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }
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

Matrix::Matrix() noexcept: Matrix(0, 0) {}

Matrix Matrix::load(std::string f_name) {
    std::ifstream in;
    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    in.open(f_name);
    try {
        std::size_t n, m;
        in >> n >> m;
        Matrix ret(n, m);

        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < m; ++j) {
                int elem;
                in >> elem;
                ret.set(i, j, elem);
            }
        }

        in.close();
        return ret;
    } catch (const std::ifstream::failure &e) {
        in.close();
        throw MatrixException("LOAD: invalid file format.");
    } catch (const std::bad_alloc &e) {
        in.close();
        throw;
    }
}

MatrixException::MatrixException() : MatrixException("") {}

MatrixException::MatrixException(std::string why) : error(why) {}

MatrixException::MatrixException(const MatrixException &other) : error(other.what()) {}

std::string MatrixException::what() const {
    return error;
}



