#ifndef IntersectionInfo_h_
#define IntersectionInfo_h_

#include "Vector3.h"
#include "Object.h"

class Object;

struct IntersectionInfo {
  float t; // Intersection distance along the ray
  const Object* object; // Object that was hit
  Vector3 hit; // Location of the intersection
};

#endif
