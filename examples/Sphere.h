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

template <typename Float>
Intersection<Float, Sphere<Float>> getPrimitiveIntersection(const Sphere<Float>& sphere, const Ray<Float>& ray) noexcept {

  const auto& center = sphere.center;
  const auto& r2 = sphere.r2;

  auto s = center - ray.o;
  auto sd = s * ray.d;
  auto ss = s * s;

  // Compute discriminant
  auto disc = sd*sd - ss + r2;

  // Complex values: No intersection
  if (disc < 0.f) {
    return Intersection<Float, Sphere<Float>>{};
  }

  // Assume we are not in a sphere... The first hit is the lesser valued
  return Intersection<Float, Sphere<Float>> {
    sd - std::sqrt(disc),
    &sphere
  };
}

template <typename Float>
Vector3<Float> getNormal(const Sphere<Float>& sphere, const Intersection<Float, Sphere<Float>>& I) noexcept {
  return normalize(I.hit - sphere.center);
}

} // namespace FastBVH
