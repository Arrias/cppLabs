#ifndef LAB_12_MATRIX_H
#define LAB_12_MATRIX_H

#include <cstdio>
#include <string>

class Matrix {
public:
    Matrix() noexcept;

    Matrix(std::size_t r, std::size_t c) noexcept(false);

    Matrix(const Matrix &m) noexcept(false);

    ~Matrix();

    std::size_t get_rows() const noexcept;

    std::size_t get_cols() const noexcept;

    void set(int i, int j, int val) noexcept(false);

    int get(int i, int j) const noexcept(false);

    void print() const;

    Matrix &operator=(const Matrix &m) noexcept(false);

    Matrix operator+(const Matrix &m) const noexcept(false);

    Matrix operator-(const Matrix &m) const noexcept(false);

    Matrix operator*(const Matrix &m) const noexcept(false);

    Matrix &operator+=(const Matrix &m) noexcept(false);

    Matrix &operator-=(const Matrix &m) noexcept(false);

    Matrix &operator*=(const Matrix &m) noexcept(false);

    bool operator==(const Matrix &m) const noexcept;

    bool operator!=(const Matrix &m) const noexcept;

    static Matrix load(std::string f_name) noexcept(false);

private:
    void init(std::size_t r, std::size_t c, int **dt = nullptr);

    std::size_t _rows{};
    std::size_t _cols{};
    int **_data{};
};

class MatrixException {
public:
    MatrixException();

    MatrixException(std::string why);

    MatrixException(const MatrixException &other);

    std::string what() const;

private:
    std::string error{};
};

#endif