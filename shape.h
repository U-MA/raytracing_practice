#ifndef _RAYTRACE_SHAPE_H_
#define _RAYTRACE_SHAPE_H_

namespace raytrace
{
  struct shape
  {
    virtual ~shape()
    {}

    // 交差判定を行う
    virtual bool intersect(const ray& ray, hitpoint* hitpoint) const = 0;

    // 色を返す
    virtual vec3 color() const = 0;

    // 発光色を返す
    virtual vec3 emission() const = 0;

    // refrection_tを返す
    virtual reflection_t reflection_type() const = 0;
  };

} // namespace raytrace

#endif // _RAYTRACE_SHAPE_H_
