#pragma once

#include <fast_bvh/Vector3.h>

namespace FastBVH {

//! Stores information regarding a ray intersection with a primitive.
//! \tparam Float The floating point type used for vector components.
//! \tparam Primitive The type of primitive used to construct the BVH.
template <typename Float, typename Primitive>
struct IntersectionInfo final {
  //! The scale at which the ray reaches the primitive.
  Float t;
  //! A pointer to the primitive that the ray intersected with.
  const Primitive* object;
  //! The point at which the ray intersects the primitive.
  Vector3<Float> hit;
};

} // namespace FastBVH
