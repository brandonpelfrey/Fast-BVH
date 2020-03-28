#pragma once

#include <fast_bvh/Vector3.h>

namespace FastBVH {

template <typename Float>
struct Ray final {

  using Vec3 = Vector3<Float>;

  Vec3 o; // Ray Origin
  Vec3 d; // Ray Direction
  Vec3 inv_d; // Inverse of each Ray Direction component

  Ray(const Vec3& o, const Vec3& d)
    : o(o), d(d), inv_d(Vec3 { 1, 1, 1 }.cdiv(d)) { }
};

} // namespace FastBVH
