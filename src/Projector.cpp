#include "pca/Projector.hpp"

#include <stdexcept>

namespace pca
{

std::vector<std::pair<double, double>> project(const std::vector<std::vector<double>>& eigenVecs)
{
    // ensure ≥2 eigenvectors

    if(eigenVecs.size() < 2)
        throw std::runtime_error("project: must have ≥2 eigenvectors");
    
    size_t N = eigenVecs[0].size();

    // ensure eigenvectors have same size

    if(eigenVecs[1].size() != N)
        throw std::runtime_error("project: eigenvectors should be same size");
    
    // project

    std::vector<std::pair<double, double>> coords;
    coords.reserve(N);

    for(size_t i = 0; i < N; i++)
        coords.push_back({eigenVecs[0][i], eigenVecs[1][i]});
    
    return coords;
}

}