#pragma once

#include "Ray.h"
#include "Vector3.h"

#include <utility>

#include <cstdint>

namespace FastBVH {

template <typename Float>
struct BBox final {

  using Vec3 = Vector3<Float>;

  Vec3 min;
  Vec3 max;
  Vec3 extent;

  constexpr BBox() noexcept { }

  constexpr BBox(const Vec3& min, const Vec3& max) noexcept
    : min(min), max(max), extent(max - min) {}

  constexpr BBox(const Vec3& p) noexcept : BBox(p, p) {}

  void expandToInclude(const Vec3& p) noexcept {
    min = FastBVH::min(min, p);
    max = FastBVH::max(max, p);
    extent = max - min;
  }

  void expandToInclude(const BBox& b) noexcept {
    min = FastBVH::min(min, b.min);
    max = FastBVH::max(max, b.max);
    extent = max - min;
  }

  bool intersect(const Ray<Float>& ray, Float *tnear, Float *tfar) const noexcept;

  uint32_t maxDimension() const noexcept;

  constexpr Float surfaceArea() const noexcept {
    return 2.0f * ((extent.x * extent.z) + (extent.x * extent.y) + (extent.y * extent.z));
  }
};

template <typename Float>
bool BBox<Float>::intersect(const Ray<Float>& ray, Float *tnear, Float *tfar) const noexcept {

  float tmin = (min.x - ray.o.x) / ray.d.x;
  float tmax = (max.x - ray.o.x) / ray.d.x;

  if (tmin > tmax) {
    std::swap(tmin, tmax);
  }

  float tymin = (min.y - ray.o.y) / ray.d.y;
  float tymax = (max.y - ray.o.y) / ray.d.y;

  if (tymin > tymax) {
    std::swap(tymin, tymax);
  }

  if ((tmin > tymax) || (tymin > tmax)) {
    return false;
  }

  if (tymin > tmin) {
    tmin = tymin;
  }

  if (tymax < tmax) {
    tmax = tymax;
  }

  float tzmin = (min.z - ray.o.z) / ray.d.z;
  float tzmax = (max.z - ray.o.z) / ray.d.z;

  if (tzmin > tzmax) {
    std::swap(tzmin, tzmax);
  }

  if ((tmin > tzmax) || (tzmin > tmax)) {
    return false;
  }

  if (tzmin > tmin) {
    tmin = tzmin;
  }

  if (tzmax < tmax) {
    tmax = tzmax;
  }

  *tnear = tmin;
  *tfar = tmax;

  return true;
}

template <typename Float>
uint32_t BBox<Float>::maxDimension() const noexcept {

  uint32_t result = 0;

  if (extent.y > extent.x) {
    result = 1;
    if (extent.z > extent.y) {
      result = 2;
    }
  } else if (extent.z > extent.x) {
    result = 2;
  }

  return result;
}

} // namespace FastBVH
