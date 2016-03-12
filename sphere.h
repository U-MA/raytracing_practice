#ifndef _RAYTRACE_SPHERE_H_
#define _RAYTRACE_SPHERE_H_

#include "material.h"
#include "shape.h"
#include "constant.h"

namespace raytrace
{

  struct sphere : public shape
  {
    sphere(double radius, const vec3& position, const raytrace::color& emission, 
           const raytrace::color& color, const reflection_t reflection_type, const raytrace::texture* texture = nullptr)
      : radius_(radius), position_(position), emission_(emission), color_(color), reflection_type_(reflection_type),
        texture_(texture)
    {}

    // rayとの交差判定を行う
    bool intersect(const ray& ray, hitpoint* hitpoint) const override
    {
      const vec3 po = position_ - ray.org;
      const double b = vec3::dot(po, ray.dir);
      const double D4 = b * b - vec3::dot(po, po) + radius_ * radius_; // 判別式

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

      hitpoint->position   = ray.org + hitpoint->distance * ray.dir;
      hitpoint->normal     = vec3::normalize(hitpoint->position - position_);

      // -pi   <= phi   <= pi
      // -pi/2 <= theta <= pi/2
      const double phi   = atan2(hitpoint->normal.z, hitpoint->normal.x);
      const double theta = asin(hitpoint->normal.y);

      // ?? 本当にこれでうまくいくか
      hitpoint->tex_coords =
        vec3(
          (phi + constant::pi) / (2 * constant::pi),
          (theta + constant::pi / 2) / constant::pi,
          0);

      return true;
    }

    vec3 color() const override {
      return color_;
    }

    vec3 emission() const override {
      return emission_;
    }

    reflection_t reflection_type() const override {
      return reflection_type_;
    }

    const raytrace::texture* texture() const override
    {
      return texture_;
    }

    double radius_;
    vec3 position_;
    raytrace::color emission_;
    raytrace::color color_;
    reflection_t reflection_type_;
    const raytrace::texture *texture_;
  };

} // namespace raytrace

#endif // _RAYTRACE_SPHERE_H_
