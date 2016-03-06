#ifndef _RAYTRACE_PPM_H_
#define _RAYTRACE_PPM_H_

#include <fstream>
#include <string>
#include <vector>

#include "material.h"

namespace raytrace
{

  // filenameにppm形式でimageの内容を書き込む
  void save_ppm(const std::string& filename, std::vector<color>& image, int width, int height)
  {
    std::ofstream ofs(filename);

    ofs << "P3" << std::endl;
    ofs << width << " " << height << std::endl;
    for (color pixel : image) {
      ofs << pixel.x << " " << pixel.y << " " << pixel.z << " ";
    }
  }

} // namespace raytrace

#endif // _RAYTRACE_PPM_H_
