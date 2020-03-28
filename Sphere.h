#pragma once

#include <fast_bvh/IntersectionInfo.h>

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
bool getPrimitiveIntersection(const Sphere<Float>& sphere, const Ray<Float>& ray, IntersectionInfo<Float, Sphere<Float>>* I) noexcept {

  const auto& center = sphere.center;
  const auto& r2 = sphere.r2;

  auto s = center - ray.o;
  auto sd = s * ray.d;
  auto ss = s * s;

  // Compute discriminant
  auto disc = sd*sd - ss + r2;

  // Complex values: No intersection
  if (disc < 0.f) {
    return false;
  }

  // Assume we are not in a sphere... The first hit is the lesser valued
  I->object = &sphere;
  I->t = sd - sqrt(disc);
  return true;
}

template <typename Float>
Vector3<Float> getNormal(const Sphere<Float>& sphere, const IntersectionInfo<Float, Sphere<Float>>& I) noexcept {
  return normalize(I.hit - sphere.center);
}

template <typename Float>
BBox<Float> getBBox(const Sphere<Float>& sphere) noexcept {
  const auto& r = sphere.r;
  return BBox<Float>(sphere.center - Vector3<Float> { r, r, r },
                     sphere.center + Vector3<Float> { r, r, r });
}

template <typename Float>
Vector3<Float> getCentroid(const Sphere<Float>& sphere) noexcept {
  return sphere.center;
}

} // namespace FastBVH
