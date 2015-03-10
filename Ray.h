#ifndef Ray_h
#define Ray_h

#include "Vector3.h"

struct Ray {
  Vector3 o; // Ray Origin
  Vector3 d; // Ray Direction
  Vector3 inv_d; // Inverse of each Ray Direction component

  Ray(const Vector3& o, const Vector3& d)
    : o(o), d(d), inv_d(Vector3(1,1,1).cdiv(d)) { }
};

#endif
