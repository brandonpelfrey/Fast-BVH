#pragma once

#include "Vector3.h"

namespace FastBVH {

struct Ray final {
  Vector3 o; // Ray Origin
  Vector3 d; // Ray Direction
  Vector3 inv_d; // Inverse of each Ray Direction component

  Ray(const Vector3& o, const Vector3& d)
    : o(o), d(d), inv_d(Vector3 { 1, 1, 1 }.cdiv(d)) { }
};

} // namespace FastBVH
