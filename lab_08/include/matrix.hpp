#pragma once

#include <cstddef>

class Matrix {
public:
    Matrix(std::size_t r, std::size_t c);

    ~Matrix();

    std::size_t get_rows() const;

    std::size_t get_cols() const;

    void set(std::size_t i, std::size_t j, int val);

    int get(std::size_t i, std::size_t j) const;

    bool operator==(const Matrix &that) const;

    bool operator!=(const Matrix &that) const;

private:
    Matrix(const Matrix &m);

    Matrix &operator=(const Matrix &m);

private:
    std::size_t _rows{};
    std::size_t _cols{};
    int **_data{};

    void init(std::size_t r, std::size_t c, int **dt = nullptr);
};