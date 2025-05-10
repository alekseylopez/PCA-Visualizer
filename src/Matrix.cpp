#include "pca/Matrix.hpp"

#include <stdexcept>

namespace pca
{

Matrix::Matrix(double rows, double cols):
    _rows(rows), _cols(cols), _data(rows * cols) {}

// multiply y = Ax

void Matrix::multiply(const std::vector<double>& x, std::vector<double>& y) const
{
    y.assign(_rows, 0);

    for(int i = 0; i < _rows; i++)
    {
        double sum = 0;

        for(int j = 0; j < _cols; j++)
            sum += x[j] * _data[index(i, j)];
        
        y[i] = sum;
    }
}

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
    
    return _data[index(i, j)];
}

double Matrix::operator()(int i, int j) const
{
    if(i < 0 || i >= _rows || j < 0 || j >= _cols)
        throw std::out_of_range("Matrix::operator() const");
    
    return _data[index(i, j)];
}

}