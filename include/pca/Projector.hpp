#ifndef PCA_PROJECTOR_HPP
#define PCA_PROJECTOR_HPP

#include <vector>
#include <utility>

namespace pca
{

std::vector<std::pair<double, double>> project(const std::vector<std::vector<double>>& eigenVecs);

}

#endif