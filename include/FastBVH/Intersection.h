#pragma once

#include <FastBVH/Vector3.h>

#include <limits>

namespace FastBVH {

//! \brief Stores information regarding a ray intersection with a primitive.
//! \tparam Float The floating point type used for vector components.
//! \tparam Primitive The type of primitive used to construct the BVH.
template <typename Float, typename Primitive>
struct Intersection final {
  /// A simple type definition for 3D vector.
  using Vec3 = Vector3<Float>;

  //! The scale at which the ray reaches the primitive.
  Float t = std::numeric_limits<Float>::infinity();

  //! A pointer to the primitive that the ray intersected with.
  const Primitive* object = nullptr;

  //! The normal at the point of intersection.
  Vec3 normal = {0, 0, 1};

  //! The UV coordinates at the position of intersection.
  Float uv[2] = {0, 0};

  //! Gets the position at the ray hit the object.
  //! \param ray_pos The ray position.
  //! \param ray_dir The ray direction.
  //! \return The position at which the intersection occurred at.
  Vec3 getHitPosition(const Vec3& ray_pos, const Vec3& ray_dir) const noexcept { return ray_pos + (ray_dir * t); }

  //! Indicates whether or not the intersection is valid.
  //! \return True if the intersection is valid, false otherwise.
  operator bool() const noexcept { return t != std::numeric_limits<Float>::infinity(); }
};

//! \brief Gets the closest of two intersections.
//! \returns A copy of either @p a or @p b, depending on which one is closer.
template <typename Float, typename Primitive>
Intersection<Float, Primitive> closest(const Intersection<Float, Primitive>& a,
                                       const Intersection<Float, Primitive>& b) noexcept {
  return (a.t < b.t) ? a : b;
}

}  // namespace FastBVH
