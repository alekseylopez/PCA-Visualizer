#include "pca/EigenSolver.hpp"

#include <stdexcept>
#include <cmath>
#include <chrono>
#include <random>
#include <limits>

namespace pca
{

// helper: dot product

static double dot(const std::vector<double>& a, const std::vector<double>&b)
{
    double dot = 0.0;
    
    int N = static_cast<int>(a.size());

    if(static_cast<int>(b.size()) != N)
        throw std::runtime_error("dot: must dot vectors of same length");
    
    for(int i = 0; i < N; i++)
        dot += a[i] * b[i];
    
    return dot;
}

// helper: norm

static double norm(const std::vector<double>& a)
{
    return std::sqrt(dot(a, a));
}

// finds first k eigenvalues

std::vector<std::vector<double>> solveTopKEigen(const Matrix& C_in, int k, double tol, int maxIter)
{
    int N = C_in.rows();

    // copy for in-place deflation

    Matrix C = C_in;

    // reserve vector for k eigenvectors

    std::vector<std::vector<double>> eigenVecs;
    eigenVecs.reserve(k);

    // random initial vector generation

    std::mt19937_64 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    // loop

    for(int mode = 0; mode < k; mode++)
    {
        std::vector<double> x(N);

        // randomly initialize x

        for(int i = 0; i < N; i++)
            x[i] = dist(rng);

        // normalize x

        double xnorm = norm(x);

        if(xnorm < std::numeric_limits<double>::epsilon())
            throw std::runtime_error("solveTopEigen: zero vector");

        for(double& xi : x)
            xi /= xnorm;
        
        // prepare for power iteration

        std::vector<double> y;

        double lambda = 0.0;

        // power iteration

        for(int iter = 0; iter < maxIter; iter++)
        {
            C.multiply(x, y);

            // Rayleigh quotient

            lambda = dot(x, y);

            // normalize y

            double ynorm = norm(y);

            if(ynorm < std::numeric_limits<double>::epsilon())
                break;
            
            for(int i = 0; i < N; i++)
                y[i] /= ynorm;
            
            // break when ||y - x|| < tol
            
            double diff = 0.0;

            for(int i = 0; i < N; i++)
            {
                double d = y[i] - x[i];

                diff += d * d;
            }
            
            x = y;

            if(diff < tol * tol)
                break;
        }

        eigenVecs.push_back(x);

        // deflate: C = C - lambda x xᵀ

        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                C(i, j) -= lambda * x[i] * x[j];
    }

    return eigenVecs;
}

}