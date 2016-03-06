#ifndef _RAYTRACE_RADIANCE_H_
#define _RAYTRACE_RADIANCE_H_

#include "intersection.h"
#include "random.h"
#include "ray.h"
#include "scene.h"

namespace raytrace
{
  color BACKGROUND_COLOR = color();
  const int DEPTH = 5;
  const int DEPTH_LIMIT = 64;

  color radiance(const ray& ray, random* rnd, int depth)
  {
    intersection intersection;

    // シーンと交差判定
    //   交差しなかったら背景と交差したとする
    if (!intersect_scene(ray, &intersection)) {
      return BACKGROUND_COLOR;
    }

    const sphere& now_object = spheres[intersection.object_id];
    const hitpoint& hitpoint = intersection.hitpoint;
    // 交差位置の法線(物体からのレイを考慮)
    //   ?? なんとなく理解
    const vec3 orienting_normal = vec3::dot(hitpoint.normal, ray.dir) < 0.0 ? hitpoint.normal : (-1.0 * hitpoint.normal);

    // 色の反射率最大のものを得る。ロシアンルーレットで使う
    // ロシアンルーレットの閾値は任意だが、色の反射率等を使うとより良い
    double russian_roulette_probability = std::max(now_object.color.x, std::max(now_object.color.y, now_object.color.z));

    // 反射回数が一定以上になったらロシアンルーレットの確率を急上昇させる
    // (スタックオーバーフロー対策)
    if (depth > DEPTH_LIMIT) {
      russian_roulette_probability *= pow(0.5, depth - DEPTH_LIMIT);
    }

    if (depth > DEPTH) {
      if (rnd->next01() >= russian_roulette_probability) {
        return now_object.emission;
      }
    } else {
      russian_roulette_probability = 1.0; // ロシアンルーレットを実行しなかった
    }

    color incoming_radiance;
    color weight = 1.0; // ?? colorクラスにリテラルを代入している

    switch (now_object.reflection_type) {
      case reflection_t::diffuse:
      {
      }
      break;

      case reflection_t::specular:
      {
      }
      break;

      case reflection_t::reflection:
      {
      }
      break;
    }
    return now_object.emission + vec3::multiply(weight, incoming_radiance);
  }
} // namespace raytrace

#endif // _RAYTRACE_RADIANCE_H_
