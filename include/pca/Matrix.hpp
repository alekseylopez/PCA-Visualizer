#ifndef PCA_MATRIX_HPP
#define PCA_MATRIX_HPP

#include <vector>

namespace pca
{

class Matrix
{
public:
    Matrix(double rows, double cols);

    int rows() const;
    int cols() const;

    double& operator()(int i, int j);
    double operator()(int i, int j) const;

private:
    int _rows, _cols;
    std::vector<double> _data;
};

}

#endif