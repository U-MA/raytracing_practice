#ifndef _RAYTRACE_TRIANGLE_H_
#define _RAYTRACE_TRIANGLE_H_

#include "shape.h"

namespace raytrace
{

  struct triangle : public shape
  {
    triangle(const vec3& v0, const vec3& v1, const vec3& v2, const raytrace::color& emission,
             const raytrace::color& color, const reflection_t reflection_type)
      : v0{v0}, v1{v1}, v2{v2}, emission_{emission}, color_{color}, reflection_type_{reflection_type}
    {}

    // rayとの交差判定を行う
    bool intersect(const ray& ray, hitpoint* hitpoint) const override
    {
      const vec3 d  = ray.dir;
      const vec3 r  = ray.org - v0;
      const vec3 e1 = v1 - v0;
      const vec3 e2 = v2 - v0;
      const vec3 u  = vec3::cross(d, e2);
      const vec3 v  = vec3::cross(r, e1);

      // divが0に近い時は、交差しないことにする
      const double div = vec3::dot(u, e1);
      if (-constant::eps < div && div < constant::eps) {
        return false;
      }

      // 三角形内で交差するための条件は
      //   beta + gamma < 1
      //   0 < beta
      //   0 < gamma

      const double beta = vec3::dot(u, r) / div;
      if (beta <= 0.0 || beta >= 1.0) {
        return false;
      }

      const double gamma = vec3::dot(v, d) / div;
      if (gamma <= 0.0 || (beta + gamma) >= 1.0) {
        return false;
      }

      // レイの始点と近い時は逆方向にレイが出ていると仮定
      // See also: eduptのSphereの交差判定
      const double t = vec3::dot(v, e2) / div;
      if (t < constant::eps) {
        return false;
      }

      hitpoint->distance = t;
      hitpoint->position = ray.org + t * ray.dir;
      vec3 c = vec3::cross(e1, e2);
      hitpoint->normal = c / c.length(); // TODO: c.length()は0にならないか?

      return true;
    }

    vec3 color() const override
    {
      return color_;
    }

    vec3 emission() const override
    {
      return emission_;
    }

    reflection_t reflection_type() const override
    {
      return reflection_type_;
    }

    // 3頂点
    vec3 v0;
    vec3 v1;
    vec3 v2;
    raytrace::color emission_;
    raytrace::color color_;
    reflection_t reflection_type_;
  };

} // namespace raytrace

#endif // _RAYTRACE_TRIANGLE_H_
