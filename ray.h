#ifndef _RAYTRACE_RAY_H_
#define _RAYTRACE_RAY_H_

namespace raytrace
{

  struct ray
  {
    ray(const vec3& org, const vec3& dir)
      :org(org), dir(dir)
    {}

    vec3 org; // 始点
    vec3 dir; // 方向
  };

}

#endif // _RAYTRACE_RAY_H_
