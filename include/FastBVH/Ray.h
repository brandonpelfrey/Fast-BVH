#pragma once

#include <FastBVH/Vector3.h>

namespace FastBVH {

//! \brief Represents a single ray.
//! Used for traversing the BVH for ray-primitive intersections.
//! \tparam Float The floating point type of the rays vector components.
template <typename Float>
struct Ray final {
  //! A simple type definition for 3D vectors used by the ray structure.
  using Vec3 = Vector3<Float>;

  //! The origin point of the ray.
  Vec3 o;

  //! The direction of the ray.
  Vec3 d;

  //! The reciprocal of the ray direction.
  //! Since the reciprocal ray direction is used
  //! quite often, saving the value here saves a
  //! lot of repetitive computations.
  Vec3 inv_d;

  //! Constructs a new ray instance.
  //! \param o The origin of the ray.
  //! \param d The direction of the ray.
  constexpr Ray(const Vec3& o, const Vec3& d) noexcept : o(o), d(d), inv_d(Vec3{1, 1, 1}.cdiv(d)) {}
};

}  // namespace FastBVH
