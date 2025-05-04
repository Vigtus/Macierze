#ifndef Matrix_H
#define Matrix_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <memory>

class Matrix {
private:
    std::unique_ptr<std::unique_ptr<int[]>[]> uniquedata;
    int** data{};
    int rows{};
    int columns{};

public:
    Matrix();
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    Matrix(int rows, int columns);
    Matrix(int rows, int columns, int* dataArray);
    ~Matrix();
    Matrix& operator=(const Matrix& other);
    Matrix& operator-(Matrix&& other) noexcept;
    void readFromFile(const std::string& filename, int rows, int colums);
    void const display();
    void add(const Matrix& other);
    void saveToFile(const char* filename) const;
    void subtract(const Matrix& other);
    void transpose();
    void multiply(const Matrix& other);
    void clear();
    void print() const;
};

#endif;