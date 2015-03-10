#ifndef BBox_h
#define BBox_h

#include "Ray.h"
#include "Vector3.h"
#include <stdint.h>

struct BBox {
  Vector3 min, max, extent;
  BBox() { }
  BBox(const Vector3& min, const Vector3& max);
  BBox(const Vector3& p);

  bool intersect(const Ray& ray, float *tnear, float *tfar) const;
  void expandToInclude(const Vector3& p);
  void expandToInclude(const BBox& b);
  uint32_t maxDimension() const;
  float surfaceArea() const;
};

#endif
