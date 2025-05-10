#include "pca/Correlator.hpp"

#include <stdexcept>
#include <vector>
#include <cmath>

namespace pca
{

Matrix buildCorrelation(const Matrix& X)
{
    int T = X.rows(), N = X.cols();

    if(T < 2)
        throw std::runtime_error("buildCorrelation: need at least 2 observations");

    // compute means of columns

    std::vector<double> mean(N, 0.0);

    for(int j = 0; j < N; j++)
    {
        double sum = 0.0;

        for(int i = 0; i < T; i++)
            sum += X(i, j);
        
        mean[j] = sum / T;
    }

    // compute normalization factors

    std::vector<double> norm(N, 0.0);

    for(int j = 0; j < N; j++)
    {
        double sumSq = 0.0;

        for(int i = 0; i < T; i++)
        {
            double d = X(i, j) - mean[j];

            sumSq += d * d;
        }

        if(sumSq == 0.0)
            throw std::runtime_error("No variance in column " + std::to_string(j));
        
        norm[j] = std::sqrt(sumSq);
    }

    // build Pearson correlation matrix:
    //     C = D^(–1/2) S D^(–1/2)
    // where
    //     H = I – (1/T) 1 1ᵀ (mean centering)
    //     S = Xᵀ H X (scatter matrix)
    //     D = diag(S_11, S_22, ..., S_NN) (consists of the diagonal of S)

    Matrix C(N, N);

    for(int j = 0; j < N; j++)
    {
        // diagonal is 1's

        C(j, j) = 1.0;

        // calculating off-diagonal elements and leveraging symmetry

        for(int k = j + 1; k < N; k++)
        {
            double dot = 0.0;

            for(int i = 0; i < T; i++)
                dot += (X(i, j) - mean[j]) * (X(i, k) - mean[k]);
            
            double corr = dot / (norm[j] * norm[k]);

            C(j, k) = corr;
            C(k, j) = corr;
        }
    }

    return C;
}

}