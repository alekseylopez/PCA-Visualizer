#ifndef PCA_MATRIX_HPP
#define PCA_MATRIX_HPP

#include <vector>

namespace pca
{

class Matrix
{
public:
    Matrix(double rows, double cols);

    void multiply(const std::vector<double>& x, std::vector<double>& y) const;

    int rows() const;
    int cols() const;

    double& operator()(int i, int j);
    double operator()(int i, int j) const;

private:
    int _rows, _cols;
    std::vector<double> _data;

    inline int index(int i, int j) const
    {
        return i * _cols + j;
    }
};

}

#endif