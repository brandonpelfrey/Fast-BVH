#pragma once

#include <FastBVH/Intersection.h>

#include <cmath>

namespace FastBVH {

//! For the purposes of demonstrating the BVH, a simple sphere
template <typename Float>
struct Sphere final {
  Vector3<Float> center; // Center of the sphere
  Float r, r2; // Radius, Radius^2

  constexpr Sphere(const Vector3<Float>& center, Float radius) noexcept
    : center(center), r(radius), r2(radius*radius) { }
};

} // namespace FastBVH
