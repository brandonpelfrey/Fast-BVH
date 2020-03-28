#pragma once

#include <FastBVH/Vector3.h>

#include <limits>

namespace FastBVH {

//! \brief Stores information regarding a ray intersection with a primitive.
//! \tparam Float The floating point type used for vector components.
//! \tparam Primitive The type of primitive used to construct the BVH.
template <typename Float, typename Primitive>
struct Intersection final {
  //! The scale at which the ray reaches the primitive.
  Float t = std::numeric_limits<Float>::infinity();
  //! A pointer to the primitive that the ray intersected with.
  const Primitive* object = nullptr;
  //! The point at which the ray intersects the primitive.
  Vector3<Float> hit = { 0, 0, 0 };
  //! Indicates whether or not the intersection is valid.
  //! \return True if the intersection is valid, false otherwise.
  operator bool () const noexcept {
    return t != std::numeric_limits<Float>::infinity();
  }
};

//! \brief Gets the closest of two intersections.
//! \returns A copy of either @p a or @p b, depending on which one is closer.
template <typename Float, typename Primitive>
Intersection<Float, Primitive> closest(const Intersection<Float, Primitive>& a,
                                       const Intersection<Float, Primitive>& b) noexcept {
  return (a.t < b.t) ? a : b;
}

} // namespace FastBVH
