#include "pca/Matrix.hpp"

#include <stdexcept>

namespace pca
{

Matrix::Matrix(double rows, double cols):
    _rows(rows), _cols(cols), _data(rows * cols) {}

// getters

int Matrix::rows() const
{
    return _rows;
}

int Matrix::cols() const
{
    return _cols;
}

// access operators

double& Matrix::operator()(int i, int j)
{
    if(i < 0 || i >= _rows || j < 0 || j >= _cols)
        throw std::out_of_range("Matrix::operator()");
    
    return _data[i + j * _cols];
}

double Matrix::operator()(int i, int j) const
{
    if(i < 0 || i >= _rows || j < 0 || j >= _cols)
        throw std::out_of_range("Matrix::operator() const");
    
    return _data[i + j * _cols];
}

}