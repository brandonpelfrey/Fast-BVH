#pragma once

#include <cmath>
#include "Object.h"

namespace FastBVH {

//! For the purposes of demonstrating the BVH, a simple sphere
struct Sphere final : public Object {
  Vector3 center; // Center of the sphere
  float r, r2; // Radius, Radius^2

  Sphere(const Vector3& center, float radius)
    : center(center), r(radius), r2(radius*radius) { }

  bool getIntersection(const Ray& ray, IntersectionInfo* I) const {
    Vector3 s = center - ray.o;
    float sd = s * ray.d;
    float ss = s * s;

    // Compute discriminant
    float disc = sd*sd - ss + r2;

    // Complex values: No intersection
    if( disc < 0.f ) return false;

    // Assume we are not in a sphere... The first hit is the lesser valued
    I->object = this;
    I->t = sd - sqrt(disc);
    return true;
  }

  Vector3 getNormal(const IntersectionInfo& I) const {
    return normalize(I.hit - center);
  }

  BBox getBBox() const {
    return BBox(center-Vector3(r,r,r), center+Vector3(r,r,r));
  }

  Vector3 getCentroid() const {
    return center;
  }

};

} // namespace FastBVH
