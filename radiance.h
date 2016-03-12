#ifndef _RAYTRACE_RADIANCE_H_
#define _RAYTRACE_RADIANCE_H_

#include "constant.h"
#include "intersection.h"
#include "random.h"
#include "ray.h"
#include "scene.h"

namespace raytrace
{
  color BACKGROUND_COLOR = color();
  const int DEPTH = 5;
  const int DEPTH_LIMIT = 64;

  color radiance(const ray& aray, random* rnd, int depth)
  {
    intersection intersection;

    // シーンと交差判定
    //   交差しなかったら背景と交差したとする
    if (!intersect_scene(aray, &intersection)) {
      return BACKGROUND_COLOR;
    }

    const shape& now_object = *g_shapes[intersection.object_id];
    const hitpoint& hitpoint = intersection.hitpoint;

    // 交差位置の法線(物体からのレイを考慮)
    //   ?? なんとなく理解
    const vec3 orienting_normal = vec3::dot(hitpoint.normal, aray.dir) < 0.0 ? hitpoint.normal : (-1.0 * hitpoint.normal);

    // 色の反射率最大のものを得る。ロシアンルーレットで使う
    // ロシアンルーレットの閾値は任意だが、色の反射率等を使うとより良い
    double russian_roulette_probability = std::max(now_object.color().x, std::max(now_object.color().y, now_object.color().z));

    // 反射回数が一定以上になったらロシアンルーレットの確率を急上昇させる
    // (スタックオーバーフロー対策)
    if (depth > DEPTH_LIMIT) {
      russian_roulette_probability *= pow(0.5, depth - DEPTH_LIMIT);
    }

    if (depth > DEPTH) {
      if (rnd->next01() >= russian_roulette_probability) {
        return now_object.emission();
      }
    } else {
      russian_roulette_probability = 1.0; // ロシアンルーレットを実行しなかった
    }

    color incoming_radiance;
    color weight = 1.0; // ?? colorクラスにリテラルを代入している

    switch (now_object.reflection_type()) {
      case reflection_t::diffuse: // 完全拡散面
      {
        // この基底に対する半球内で次の例を飛ばす
        vec3 w, u, v;
        w = orienting_normal;

        // ベクトルwと直交するベクトルを作る。w.xが0に近い場合とそうで無い場合とで使うベクトルを変える
        if (fabs(w.x) > constant::eps) { 
          u = vec3::normalize(vec3::cross(vec3(0.0, 1.0, 0.0), w));
        } else {
          u = vec3::normalize(vec3::cross(vec3(1.0, 0.0, 0.0), w));
        }
        v = vec3::cross(w, u);

        // コサイン項を使った重点的サンプリング
        const double r1 = 2 * constant::pi * rnd->next01();
        const double r2 = rnd->next01(), r2s = sqrt(r2);
        vec3 dir = vec3::normalize(u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1.0 - r2));

        incoming_radiance = radiance(ray(hitpoint.position, dir), rnd, depth+1);

        if (now_object.texture()) {
          weight = vec3::multiply(now_object.color(), now_object.texture()->color(hitpoint.tex_coords));
        } else {
          weight = now_object.color() / russian_roulette_probability;
        }
      }
      break;

      case reflection_t::specular:
      {
        // 完全鏡面なのでレイの反射方向は決定的
        // ロシアンルーレットの確率で除算するのは上と同じ
        vec3 dir = aray.dir - hitpoint.normal * 2.0 * vec3::dot(hitpoint.normal, aray.dir);
        incoming_radiance = radiance(ray(hitpoint.position, dir),rnd, depth+1);

        weight = now_object.color() / russian_roulette_probability;
      }
      break;

      case reflection_t::reflection: // 屈折率iorのガラス
      {
        const ray reflection_ray = ray(hitpoint.position, aray.dir - hitpoint.normal * 2.0 * vec3::dot(hitpoint.normal, aray.dir));
        const bool into = vec3::dot(hitpoint.normal, orienting_normal) > 0.0; // レイがオブジェクトから出るのか、入るのか

        // Snellの法則
        const double nc = 1.0; // 真空の屈折率
        const double nt = ior;
        const double nnt = into ? nc / nt : nt / nc;
        const double ddn = vec3::dot(aray.dir, orienting_normal);
        const double cos2t = 1.0 - nnt * nnt * (1.0 - ddn * ddn);

        if (cos2t < 0.0) { // 全反射
          incoming_radiance = radiance(reflection_ray, rnd, depth+1);
          weight = now_object.color() / russian_roulette_probability;
          break;
        }

        // 屈折の法則
        const ray refraction_ray = ray(hitpoint.position,
            vec3::normalize(aray.dir * nnt - hitpoint.normal * (into ? 1.0 : -1.0) * (ddn * nnt + sqrt(cos2t))));

        // SchlickによるFresnelの反射係数の近似を使用
        const double a = nt - nc, b = nt + nc;
        const double R0 = (a * a) / (b * b);

        const double c = 1.0 - (into ? -ddn : vec3::dot(refraction_ray.dir, -1.0 * orienting_normal));
        const double Re = R0 + (1.0 - R0) * pow(c, 5.0);
        const double nnt2 = pow(into ? nc / nt : nt / nc, 2.0);
        const double Tr = (1.0 - Re) * nnt2;

        const double probability = 0.25 + 0.5 * Re;

        if (depth > 2) {
          if (rnd->next01() < probability) {
            incoming_radiance = radiance(reflection_ray, rnd, depth+1) * Re;
            weight = now_object.color() / (probability * russian_roulette_probability);
          } else {
            incoming_radiance = radiance(refraction_ray, rnd, depth+1) * Tr;
            weight = now_object.color() / ((1.0 - probability) * russian_roulette_probability);
          }
        } else {
          incoming_radiance =
            radiance(reflection_ray, rnd, depth+1) * Re +
            radiance(refraction_ray, rnd, depth+1) * Tr;
          weight = now_object.color() / russian_roulette_probability;
        }
      }
      break;
    }

    return now_object.emission() + vec3::multiply(weight, incoming_radiance);
  }
} // namespace raytrace

#endif // _RAYTRACE_RADIANCE_H_
