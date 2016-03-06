#ifndef _RAYTRACE_RENDER_H_
#define _RAYTRACE_RENDER_H_

#include <iostream>
#include <vector>

#include "material.h"
#include "radiance.h"

namespace raytrace
{

  // width x heightの画像をレンダリングする
  //   各ピクセルはsupersamples x supersamplesのサブピクセルに分割
  //   1つのサブピクセルあたりsamples回のサンプリングを行う
  std::vector<color> render(int width, int height, int samples, int supersamples)
  {
    // カメラ位置
    const vec3 camera_position = vec3(50.0, 52.0, 220.0);
    const vec3 camera_dir      = vec3::normalize(vec3(0.0, -0.04, -1.0));
    const vec3 camera_up       = vec3(0.0, 1.0, 0.0);

    // ワールド座標系でのスクリーンの大きさ
    // スクリーンの大きさは(2 x screen_width, 2 x screen_height)
    // スクリーンの原点は左下
    const double screen_width  = 30.0 * width / height;
    const double screen_height = 30.0;

    // カメラからスクリーンまでの距離
    const double screen_dist = 40.0;

    // スクリーンを張るベクトル
    //   ?? vec3::cross(screen_x, camera_dir)の引数を変えるとダメなのか
    const vec3 screen_x = vec3::normalize(vec3::cross(camera_dir, camera_up)) * screen_width;
    const vec3 screen_y = vec3::normalize(vec3::cross(screen_x, camera_dir)) * screen_height;
    const vec3 screen_center = camera_position + camera_dir * screen_dist;

    std::vector<color> image(width * height, color());

    for (int y = 0; y < height; ++y) {
      std::cerr << "Rendering (y = " << y << ") " << (100.0 * y / (height-1)) << "%" << std::endl;

      random rnd(y + 1);
      for (int x = 0; x < width; ++x) {
        const int image_idx = (height - y - 1) * width + x;

        // supersamples x supersamplesのスーパーサンプリング
        for (int sy = 0; sy < supersamples; ++sy) {
          for (int sx = 0; sx < supersamples; ++sx) {
            color accum_radiance;

            // 各サブピクセルからレイを飛ばすために
            // サブピクセルのスクリーン座標を求める
            // サブピクセルも左下が原点
            //   ?? eduptはこの処理を次のfor文内に記述している
            //      何か意図はあるのだろうか

            // rx(ry)でsx(sy)にrateをかけているのは
            // スクリーン座標に統一するため
            const double rate = 1.0 / supersamples;
            const double rx = sx * rate + rate / 2.0;
            const double ry = sy * rate + rate / 2.0;

            // サブピクセルの中央の点のスクリーン座標
            //   ?? 数学的になぜこれでうまくいくのかがわかってない
            const vec3 screen_position =
              screen_center +
              screen_x * ((rx + x) / width - 0.5) +
              screen_y * ((ry + y) / height - 0.5);

            // レイを飛ばす方向
            // カメラからサブピクセル方向
            const vec3 dir = vec3::normalize(screen_position - camera_position);

            // 1つのサブピクセルにつき、samples回サンプリング
            for (int s = 0; s < samples; ++s) {
              // カメラからサブピクセルのスクリーン座標に向かってレイを飛ばす
              accum_radiance += radiance(ray(camera_position, dir), &rnd, 0) / (samples * (supersamples * supersamples));
            }
            image[image_idx] += accum_radiance;
          }
        }
      }
    }
    return image;
  }

} // namespace raytrace

#endif // _RAYTRACE_RENDER_H_
