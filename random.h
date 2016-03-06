#ifndef _RAYTRACE_RANDOM_H_
#define _RAYTRACE_RANDOM_H_

#include <climits>

namespace raytrace
{

  class xorshift
  {
  public:
    xorshift(unsigned int s)
    {
      seed_[0] = 123456789;
      seed_[1] = 362436069;
      seed_[2] = 521288629;
      seed_[3] = s;
    }

    int next()
    {
      unsigned int x = seed_[0] ^ (seed_[0] << 11);
      seed_[0] = seed_[1];
      seed_[1] = seed_[2];
      seed_[2] = seed_[3];
      seed_[3] = (seed_[3] ^ (seed_[3] >> 19)) ^ ( x ^ (x >> 8));
      return seed_[3];
    }

    double next01()
    {
      return static_cast<double>(next()) / UINT_MAX;
    }

  private:
    unsigned int seed_[4];
  };

  typedef xorshift random;

} // namespace raytrace

#endif // _RAYTRACE_RANDOM_H_
