#include <iostream>

#include "ppm.h"

int main()
{
  std::cout << "raytracing practice" << std::endl;

  const int width  = 640;
  const int height = 480;

  std::vector<raytrace::color> image;

  raytrace::save_ppm(std::string("image.ppm"), image, width, height);

  return 0;
}
