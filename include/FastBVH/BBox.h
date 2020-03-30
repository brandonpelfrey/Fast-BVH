#pragma once

#include <FastBVH/Ray.h>
#include <FastBVH/Vector3.h>

#include <cstdint>
#include <utility>

namespace FastBVH {

//! \brief Represents an axis-aligned bounding box.
//! This could also be called an AABB.
//! It's used to represent the space occupied
//! by a primitive.
//! \tparam Float The floating point type used
//! by the minimum and maximum point components.
template <typename Float>
struct BBox final {
  //! A simple type definition for a 3D vector.
  using Vec3 = Vector3<Float>;

  //! The minimum point of the bounding box.
  Vec3 min;

  //! The maximum point of the bounding box.
  Vec3 max;

  //! The difference between the max and min
  //! points of the bounding box.
  Vec3 extent;

  //! Constructs an uninitialized bounding box.
  constexpr BBox() noexcept {}

  //! Constructs a bounding box with
  //! a specified minimum and maximum.
  constexpr BBox(const Vec3& min, const Vec3& max) noexcept : min(min), max(max), extent(max - min) {}

  //! Constructs a bounding box around
  //! a single point. The volume occupied
  //! by the box after using this construction
  //! will always be zero.
  constexpr BBox(const Vec3& p) noexcept : BBox(p, p) {}

  //! Expands the volume of the bounding box to fit a new point.
  //! \param p The point to expand the volume for.
  void expandToInclude(const Vec3& p) noexcept {
    min = FastBVH::min(min, p);
    max = FastBVH::max(max, p);
    extent = max - min;
  }

  //! Expands the volume of the bounding box to fit the space of another box.
  //! \param b The box to expand the volume for.
  void expandToInclude(const BBox& b) noexcept {
    min = FastBVH::min(min, b.min);
    max = FastBVH::max(max, b.max);
    extent = max - min;
  }

  //! Gets the center of the bounding box.
  //! \return The center of the bounding box.
  Vec3 getCenter() const noexcept { return (max + min) * Float(0.5); }

  //! Checks for intersection between a ray and the box.
  //! \param ray The ray being traced.
  //! \param tnear The scale to the nearest box hit.
  //! \param tfar The scale to the farthest box hit.
  //! \return True if the ray hits the box, false otherwise.
  bool intersect(const Ray<Float>& ray, Float* tnear, Float* tfar) const noexcept;

  //! Determines the index of the dimension
  //! that has the largest space between the
  //! minimum and maximum points of the box.
  //! \return The index of the dimension that
  //! has the most amount of space between the
  //! minimum and maximum box points. A value of
  //! zero indicates the X-axis, a value of one
  //! indicates the Y-axis, and a value of two
  //! indicates the Z-axis.
  uint32_t maxDimension() const noexcept;

  //! Calculates the surface area of the box.
  //! \return The surface area of the bounding box.
  constexpr Float surfaceArea() const noexcept {
    return Float(2) * ((extent.x * extent.z) + (extent.x * extent.y) + (extent.y * extent.z));
  }
};

template <typename Float>
bool BBox<Float>::intersect(const Ray<Float>& ray, Float* tnear, Float* tfar) const noexcept {
  Float tmin = (min.x - ray.o.x) * ray.inv_d.x;
  Float tmax = (max.x - ray.o.x) * ray.inv_d.x;

  if (tmin > tmax) {
    std::swap(tmin, tmax);
  }

  Float tymin = (min.y - ray.o.y) * ray.inv_d.y;
  Float tymax = (max.y - ray.o.y) * ray.inv_d.y;

  if (tymin > tymax) {
    std::swap(tymin, tymax);
  }

  if ((tmin > tymax) || (tymin > tmax)) {
    return false;
  }

  tmin = std::fmax(tymin, tmin);
  tmax = std::fmin(tymax, tmax);

  Float tzmin = (min.z - ray.o.z) * ray.inv_d.z;
  Float tzmax = (max.z - ray.o.z) * ray.inv_d.z;

  if (tzmin > tzmax) {
    std::swap(tzmin, tzmax);
  }

  if ((tmin > tzmax) || (tzmin > tmax)) {
    return false;
  }

  tmin = std::fmax(tzmin, tmin);
  tmax = std::fmin(tzmax, tmax);

  *tnear = tmin;
  *tfar = tmax;

  return true;
}

template <typename Float>
uint32_t BBox<Float>::maxDimension() const noexcept {
  // Assume X axis is longest first
  uint32_t result = 0;

  if (extent[1] > extent[result]) result = 1;

  if (extent[2] > extent[result]) result = 2;

  return result;
}

}  // namespace FastBVH
