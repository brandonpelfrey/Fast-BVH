#pragma once

#include "Vector3.h"
#include "Object.h"

namespace FastBVH {

template <typename Float>
struct Object;

template <typename Float>
struct IntersectionInfo final {
  Float t; // Intersection distance along the ray
  const Object<Float>* object; // Object that was hit
  Vector3<Float> hit; // Location of the intersection
};

} // namespace FastBVH
