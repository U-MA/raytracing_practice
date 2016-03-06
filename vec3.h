#ifndef _RAYTRACE_VEC3_H_
#define _RAYTRACE_VEC3_H_

namespace raytrace
{

  struct vec3
  {
    vec3()
      : x(0), y(0), z(0)
    {}

    int x;
    int y;
    int z;
  };

} // namespace raytrace

#endif // _RAYTRACE_VEC3_H_
