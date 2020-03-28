#pragma once

#include "Vector3.h"
#include "Object.h"

namespace FastBVH {

class Object;

struct IntersectionInfo final {
  float t; // Intersection distance along the ray
  const Object* object; // Object that was hit
  Vector3 hit; // Location of the intersection
};

} // namespace FastBVH
