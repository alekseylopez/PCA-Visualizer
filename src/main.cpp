#include "pca/DataLoader.hpp"
#include "pca/Matrix.hpp"
#include "pca/Correlator.hpp"
#include "pca/EigenSolver.hpp"
#include "pca/Projector.hpp"
#include "pca/Renderer.hpp"

#include <iostream>
#include <string>

using namespace pca;

int main(int argc, char** argv)
{
    if(argc != 2)
        throw std::invalid_argument("Usage: ./pca <file_name>");
    
    std::string s = argv[1];

    Matrix X = loadData(s);

    Matrix C = buildCorrelation(X);

    std::vector<std::vector<double>> eigenVecs = solveTopKEigen(C, 2);

    std::vector<std::pair<double, double>> coords = project(eigenVecs);

    writeScatterPPM(coords, 600, 600, "pca_scatter.ppm");

    return 0;
}