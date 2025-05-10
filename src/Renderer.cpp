#include "pca/Renderer.hpp"

#include <fstream>
#include <algorithm>
#include <limits>

namespace pca
{

void writeScatterPPM(const std::vector<std::pair<double, double>>& points, int width, int height, const std::string& filename)
{
    double xmin =  std::numeric_limits<double>::infinity();
    double xmax = -std::numeric_limits<double>::infinity();
    double ymin =  std::numeric_limits<double>::infinity();
    double ymax = -std::numeric_limits<double>::infinity();

    for(auto& [x,y] : points)
    {
        xmin = std::min(xmin, x);
        xmax = std::max(xmax, x);
        ymin = std::min(ymin, y);
        ymax = std::max(ymax, y);
    }

    // slight padding for visibility

    double xpad = (xmax - xmin) * 0.05;
    double ypad = (ymax - ymin) * 0.05;
    xmin -= xpad;
    xmax += xpad;
    ymin -= ypad;
    ymax += ypad;

    // white background buffer

    std::vector<unsigned char> img(width * height * 3, 255);

    // plot each point as a 3x3 pixel square
    
    for(auto& [x,y] : points)
    {
        int px = int((x - xmin) / (xmax - xmin) * (width  - 1));
        int py = int((y - ymin) / (ymax - ymin) * (height - 1));

        // flip y for image coordinates

        py = (height - 1) - py;
        for(int dy = -1; dy <= 1; ++dy)
        {
            for(int dx = -1; dx <= 1; ++dx)
            {
                int xx = px + dx, yy = py + dy;

                if(xx < 0 || xx >= width || yy < 0 || yy >= height)
                    continue;

                size_t idx = (yy * width + xx) * 3;
                img[idx + 0] = img[idx + 1] = img[idx + 2] = 0;
            }
        }
    }

    std::ofstream fout(filename, std::ios::binary);
    fout << "P6\n" << width << ' ' << height << "\n255\n";
    fout.write(reinterpret_cast<char*>(img.data()), img.size());
}

}