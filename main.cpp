#include <iostream>

#include "ppm.h"
#include "render.h"

int main()
{
  std::cout << "raytracing practice" << std::endl;

  const int width        = 640;
  const int height       = 480;
  const int samples      = 16;
  const int supersamples = 8;

  std::cout << width << "x" << height << " " << samples * (supersamples * supersamples) <<
    " samples per pixels" << std::endl;
  std::vector<raytrace::color> image = raytrace::render(width, height, samples, supersamples);

  raytrace::save_ppm(std::string("image.ppm"), image, width, height);

  return 0;
}
