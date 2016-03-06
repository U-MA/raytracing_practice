#ifndef _RAYTRACE_MATERIAL_H_
#define _RAYTRACE_MATERIAL_H_

#include "vec3.h"

namespace raytrace
{
  typedef vec3 color;

  enum class reflection_t
  {
    diffuse,    // 完全拡散面
    specular,  // 理想的な鏡面
    reflection, // 理想的なガラス的物質
  };

  const double ior = 1.5; // 屈折率(Index of reflection)
}

#endif // _RAYTRACE_MATERIAL_H_
