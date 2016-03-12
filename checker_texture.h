#ifndef _RAYTRACE_CHECKER_TEXTURE_H_
#define _RAYTRACE_CHECKER_TEXTURE_H_

namespace raytrace
{
  #define WIDTH  64
  #define HEIGHT 64

  struct checker_texture : public texture
  {
    checker_texture()
      : data{new raytrace::color[WIDTH * HEIGHT]}
    {
      // チェッカーパターンの生成
      for (int y=0; y < HEIGHT; ++y) {
        for (int x=0; x < WIDTH; ++x) {
          const double c = (((y&0x8)==0)^((x&0x8)==0)) * 1.0;
          data[y * WIDTH + x] = raytrace::color(c, c, c);
          std::cout << "x: " << x << " y: " << y << " => " << c << std::endl;
        }
      }
    }

    virtual raytrace::color color(const vec3& v) const override
    {
      const int x = static_cast<int>(v.x * WIDTH);
      const int y = static_cast<int>(v.y * HEIGHT);
      return data[y * WIDTH + x];
    }

    std::unique_ptr<raytrace::color[]> data;
  };
} // namespace raytrace

#endif // _RAYTRACE_CHECKER_TEXTURE_H_
