#include "pca/DataLoader.hpp"
#include "pca/Matrix.hpp"
#include "pca/Correlator.hpp"

#include <iostream>
#include <string>

using namespace pca;

int main(int argc, char** argv)
{
    if(argc != 2)
        throw std::invalid_argument("Usage: ./pca <file_name>");
    
    std::string s = argv[1];

    Matrix X = loadData(s);

    for(int i = 0; i < X.rows(); i++)
    {
        for(int j = 0; j < X.cols(); j++)
        {
            std::cout << X(i, j) << " ";
        }

        std::cout << "\n";
    }

    std::cout << "---\n";

    Matrix C = buildCorrelation(X);

    for(int i = 0; i < C.rows(); i++)
    {
        for(int j = 0; j < C.cols(); j++)
        {
            std::cout << C(i, j) << " ";
        }

        std::cout << "\n";
    }

    return 0;
}