#ifndef PCA_DATALOADER_HPP
#define PCA_DATALOADER_HPP

#include "pca/Matrix.hpp"

#include <string>

namespace pca
{

Matrix loadData(const std::string& filename);

}

#endif