#include "BBox.h"

#include <algorithm>

namespace FastBVH {

BBox::BBox(const Vector3& min, const Vector3& max)
  : min(min), max(max) { extent = max - min; }

BBox::BBox(const Vector3& p)
  : min(p), max(p) { extent = max - min; }

void BBox::expandToInclude(const Vector3& p) {
  min = FastBVH::min(min, p);
  max = FastBVH::max(max, p);
  extent = max - min;
}

void BBox::expandToInclude(const BBox& b) {
  min = FastBVH::min(min, b.min);
  max = FastBVH::max(max, b.max);
  extent = max - min;
}

uint32_t BBox::maxDimension() const {
  uint32_t result = 0;
  if(extent.y > extent.x) {
    result = 1;
    if(extent.z > extent.y) result = 2;
  } else if(extent.z > extent.x) result = 2;
  
  return result;
}

float BBox::surfaceArea() const {
  return 2.f*( extent.x*extent.z + extent.x*extent.y + extent.y*extent.z );
}

bool BBox::intersect(const Ray& ray, float *tnear, float *tfar) const {

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

} // namespace FastBVH
