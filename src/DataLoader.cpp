#include "pca/DataLoader.hpp"

#include <fstream>
#include <stdexcept>
#include <vector>
#include <sstream>

namespace pca
{

Matrix loadData(const std::string& filename)
{
    // make a input stream

    std::ifstream fin(filename);
    if(!fin)
        throw std::runtime_error("loadData: invalid file name");
    
    // load data
    
    std::vector<std::vector<double>> temp;
    std::string line;

    std::getline(fin, line);
    
    while(std::getline(fin, line))
    {
        if(line.empty())
            continue;
        
        std::vector<double> row;

        // string stream for the line

        std::stringstream ss(line);

        std::string cell;

        // read from the line

        while(std::getline(ss, cell, ','))
        {
            try
            {
                row.push_back(std::stod(cell));
            } catch(...)
            {
                throw std::runtime_error("loadData: invalid number in CSV: " + cell);
            }
        }

        temp.push_back(std::move(row));
    }

    size_t T = temp.size(), N = temp[0].size();

    // ensure matrix is valid

    for(size_t i = 1; i < T; i++)
        if(temp[i].size() != N)
            throw std::runtime_error("loadData: inconsistent column at line " + std::to_string(i + 1));

    // build matrix

    Matrix X(static_cast<int>(T), static_cast<int>(N));

    for(size_t i = 0; i < T; i++)
        for(size_t j = 0; j < N; j++)
            X(static_cast<int>(i), static_cast<int>(j)) = temp[i][j];
    
    return X;
}

}