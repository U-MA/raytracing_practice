#ifndef _RAYTRACE_TEXTURE_H_
#define _RAYTRACE_TEXTURE_H_

namespace raytrace
{

  struct texture
  {
    virtual ~texture()
    {}

    virtual raytrace::color color(const vec3& v) const = 0;
  };

} // namespace raytrace

#endif // _RAYTRACE_TEXTURE_H_
