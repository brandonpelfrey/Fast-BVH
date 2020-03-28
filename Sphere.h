#pragma once

#include <cmath>
#include "Object.h"

namespace FastBVH {

//! For the purposes of demonstrating the BVH, a simple sphere
template <typename Float>
struct Sphere final : public Object<Float> {
  Vector3<Float> center; // Center of the sphere
  Float r, r2; // Radius, Radius^2

  Sphere(const Vector3<Float>& center, Float radius)
    : center(center), r(radius), r2(radius*radius) { }

  bool getIntersection(const Ray<Float>& ray, IntersectionInfo<Float>* I) const noexcept override {

    auto s = center - ray.o;
    auto sd = s * ray.d;
    auto ss = s * s;

    // Compute discriminant
    Float disc = sd*sd - ss + r2;

    // Complex values: No intersection
    if( disc < 0.f ) return false;

    // Assume we are not in a sphere... The first hit is the lesser valued
    I->object = this;
    I->t = sd - sqrt(disc);
    return true;
  }

  Vector3<Float> getNormal(const IntersectionInfo<Float>& I) const noexcept override {
    return normalize(I.hit - center);
  }

  BBox<Float> getBBox() const noexcept override {
    return BBox<Float>(center - Vector3<Float> { r, r, r },
                       center + Vector3<Float> { r, r, r });
  }

  Vector3<Float> getCentroid() const noexcept override {
    return center;
  }
};

} // namespace FastBVH
