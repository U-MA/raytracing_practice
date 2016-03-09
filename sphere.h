#ifndef _RAYTRACE_SPHERE_H_
#define _RAYTRACE_SPHERE_H_

#include "constant.h"

namespace raytrace
{

  struct sphere
  {
    sphere(double radius, const vec3& position, const color& emission, const color& color, const reflection_t reflection_type)
      : radius(radius), position(position), emission(emission), color(color), reflection_type(reflection_type)
    {}

    // rayとの交差判定を行う
    bool intersect(const ray& ray, hitpoint* hitpoint) const
    {
      const vec3 po = position - ray.org;
      const double b = vec3::dot(po, ray.dir);
      const double D4 = b * b - vec3::dot(po, po) + radius * radius; // 判別式

      if (D4 < 0.0) {
        return false;
      }

      const double sqrt_D4 = sqrt(D4);
      const double t1 = b - sqrt_D4, t2 = b + sqrt_D4;

      if (t1 < constant::eps && t2 < constant::eps) {
        return false;
      }

      if (t1 > constant::eps) {
        hitpoint->distance = t1;
      } else {
        hitpoint->distance = t2;
      }

      hitpoint->position = ray.org + hitpoint->distance * ray.dir;
      hitpoint->normal   = vec3::normalize(hitpoint->position - position);
      return true;
    }

    double radius;
    vec3 position;
    color emission;
    color color;
    reflection_t reflection_type;
  };

} // namespace raytrace

#endif // _RAYTRACE_SPHERE_H_
