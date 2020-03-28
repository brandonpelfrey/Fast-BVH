#pragma once

#include <FastBVH/BBox.h>
#include <FastBVH/IntersectionInfo.h>
#include <FastBVH/Ray.h>

namespace FastBVH {

template <typename Float>
struct Object {
#if 0
  //! All "Objects" must be able to test for intersections with rays.
  virtual bool getIntersection(const Ray<Float>& ray, IntersectionInfo<Float>* intersection) const noexcept {
    (void)ray;
    (void)intersection;
    return false;
  }

  //! Return an object normal based on an intersection
  virtual Vector3<Float> getNormal(const IntersectionInfo<Float>& I) const noexcept {
    (void)I;
    return Vector3<Float> { 0, 0, 1 };
  }

  //! Return a bounding box for this object
  virtual BBox<Float> getBBox() const noexcept {
    return BBox<Float>(Vector3<Float> { 0, 0, 0 });
  }

  //! Return the centroid for this object. (Used in BVH Sorting)
  virtual Vector3<Float> getCentroid() const noexcept {
    return Vector3<Float> { 0, 0, 0 };
  }
#endif
};

} // namespace FastBVH
