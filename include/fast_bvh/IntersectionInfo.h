#pragma once

#include <fast_bvh/Vector3.h>

namespace FastBVH {

template <typename Float, typename Primitive>
struct IntersectionInfo final {
  Float t; // Intersection distance along the ray
  const Primitive* object; // Object that was hit
  Vector3<Float> hit; // Location of the intersection
};

} // namespace FastBVH
