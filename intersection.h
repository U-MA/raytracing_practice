#ifndef _RAYTRACE_INTERSECTION_H_
#define _RAYTRACE_INTERSECTION_H_

#include "constant.h"

namespace raytrace
{

  struct hitpoint
  {
    hitpoint()
      : distance(constant::inf), normal(), position()
    {}

    double distance;
    vec3 normal;
    vec3 position;
  };

  struct intersection
  {
    intersection()
      : object_id(-1)
    {}

    hitpoint hitpoint;
    int object_id;
  };

} // namespace raytrace

#endif // _RAYTRACE_INTERSECTION_H_
