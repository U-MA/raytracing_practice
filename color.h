#ifndef _RAYTRACE_COLOR_H_
#define _RAYTRACE_COLOR_H_

namespace raytrace {

  struct Color
  {
    Color()
      : x(0), y(0), z(0)
    {}

    int x;
    int y;
    int z;
  };

} // namespace raytrace

#endif // _RAYTRACE_COLOR_H_
