#ifndef PCA_RENDERER_HPP
#define PCA_RENDERER_HPP

#include <vector>
#include <utility>
#include <string>

namespace pca
{

void writeScatterPPM(const std::vector<std::pair<double, double>>& points, int width, int height, const std::string& filename);

}

#endif