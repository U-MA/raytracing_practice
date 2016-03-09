#ifndef _RAYTRACE_PPM_H_
#define _RAYTRACE_PPM_H_

#include <fstream>
#include <string>
#include <vector>

#include "material.h"

namespace raytrace
{
  double clamp(double x) {
    if (x < 0.0) {
      return 0.0;
    } else if (x > 1.0) {
      return 1.0;
    }
    return x;
  }

  int to_int(double x) {
    return static_cast<int>(pow(clamp(x), 1/2.2) * 255 + 0.5);
  }

  // filenameにppm形式でimageの内容を書き込む
  void save_ppm(const std::string& filename, std::vector<color>& image, int width, int height)
  {
    std::ofstream ofs(filename);

    ofs << "P3" << std::endl;
    ofs << width << " " << height << std::endl;
    ofs << 255 << std::endl;
    for (color pixel : image) {
      ofs << to_int(pixel.x) << " " << 
             to_int(pixel.y) << " " << 
             to_int(pixel.z) << " ";
    }
  }

} // namespace raytrace

#endif // _RAYTRACE_PPM_H_
