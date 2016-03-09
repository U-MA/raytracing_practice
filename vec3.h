#ifndef _RAYTRACE_VEC3_H_
#define _RAYTRACE_VEC3_H_

#include <cmath>

namespace raytrace
{

  struct vec3
  {
    vec3(double ax = 0, double ay = 0, double az = 0)
      : x(ax), y(ay), z(az)
    {}

    // 大きさを1にする
    static vec3 normalize(const vec3& v)
    {
      return v * (1.0 / v.length());
    }

    // 内積を求める
    static double dot(const vec3& v1, const vec3& v2)
    {
      return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    // 外積を求める
    static vec3 cross(const vec3& v1, const vec3& v2)
    {
      return vec3(
          (v1.y * v2.z) - (v1.z * v2.y),
          (v1.z * v2.x) - (v1.x * v2.z),
          (v1.x * v2.y) - (v1.y * v2.x));
    }

    static vec3 multiply(const vec3& v1, const vec3& v2)
    {
      return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

    // 大きさの2乗
    double length_squred() const
    {
      return x * x + y * y + z * z;
    }

    double length() const
    {
      return std::sqrt(length_squred());
    }

    vec3 operator+(const vec3& rhs) const
    {
      return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
    }

    vec3 operator-(const vec3& rhs) const
    {
      return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    vec3 operator*(double rhs) const
    {
      return vec3(x * rhs, y * rhs, z * rhs);
    }

    vec3 operator/(double rhs) const
    {
      return vec3(x / rhs, y / rhs, z / rhs);
    }

    double x;
    double y;
    double z;
  };

  vec3 operator*(double d, const vec3& v)
  {
    return v * d;
  }

} // namespace raytrace


#endif // _RAYTRACE_VEC3_H_
