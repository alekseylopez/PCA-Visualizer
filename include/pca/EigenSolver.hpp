#ifndef PCA_EIGENSOLVER_HPP
#define PCA_EIGENSOLVER_HPP

#include "pca/Matrix.hpp"

#include <vector>

namespace pca
{

std::vector<std::vector<double>> solveTopKEigen(const Matrix& C_in, int k, double tol = 1e-6, int maxIter = 1000);

}

#endif