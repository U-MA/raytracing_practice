#ifndef _RAYTRACE_SCENE_H_
#define _RAYTRACE_SCENE_H_

#include "sphere.h"

namespace raytrace
{

  const std::vector<sphere> spheres = {
    sphere(1e5,  vec3(1e5+1,   40.8, 81.6),      color(),           color(0.75, 0.25, 0.25), reflection_t::diffuse),    // 左
    sphere(1e5,  vec3(-1e5+99, 40.8, 81.6),      color(),           color(0.25, 0.25, 0.75), reflection_t::diffuse),    // 右
    sphere(1e5,  vec3(50.0,    40.8, 81.6),      color(),           color(0.75, 0.75, 0.75), reflection_t::diffuse),    // 奥
    sphere(1e5,  vec3(50.0,    40.8, 81.6),      color(),           color(),                 reflection_t::diffuse),    // 手前
    sphere(1e5,  vec3(50.0,    1e5, 81.6),       color(),           color(0.75, 0.75, 0.75), reflection_t::diffuse),    // 床
    sphere(1e5,  vec3(50.0,    -1e5+81.6, 81.6), color(),           color(0.75, 0.75, 0.75), reflection_t::diffuse),    // 天井
    sphere(20.0, vec3(65.0,    20.0, 81.6),      color(),           color(0.25, 0.75, 0.25), reflection_t::diffuse),    // 緑球
    sphere(16.5, vec3(27.0,    16.5, 81.6),      color(),           color(0.99, 0.99, 0.99), reflection_t::specular),   // 鏡
    sphere(16.5, vec3(77.0,    16.5, 81.6),      color(),           color(0.99, 0.99, 0.99), reflection_t::reflection), // ガラス
    sphere(15.0, vec3(50.0,    90.0, 81.6),      color(36, 36, 36), color(),                 reflection_t::diffuse),    // 照明
  };

  // シーンとの交差判定
  bool intersect_scene(const ray& ray, intersection* intersection)
  {
    const double n = sizeof(spheres) / sizeof(sphere);

    // intersectionの初期化
    intersection->hitpoint.distance = constant::inf;
    intersection->object_id = -1;

    // 線形探索
    for (int i = 0; i < static_cast<int>(n); ++i) {
      hitpoint hitpoint;
      if (spheres[i].intersect(ray, &hitpoint)) {
        if (hitpoint.distance < intersection->hitpoint.distance) {
          intersection->hitpoint = hitpoint;
          intersection->object_id = i;
        }
      }
    }

    return intersection->object_id != -1;
  }

} // namespace raytrace

#endif // _RAYTRACE_SCENE_H_
