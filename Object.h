#ifndef Object_h_
#define Object_h_

#include "IntersectionInfo.h"
#include "Ray.h"
#include "BBox.h"


namespace pelfrey {
struct Object {
  //! All "Objects" must be able to test for intersections with rays.
  virtual bool getIntersection(
      const Ray& ray,
      IntersectionInfo* intersection)
    const = 0;

  //! Return an object normal based on an intersection
  virtual Vector3 getNormal(const IntersectionInfo& I) const = 0;

  //! Return a bounding box for this object
  virtual BBox getBBox() const = 0;

  //! Return the centroid for this object. (Used in BVH Sorting)
  virtual Vector3 getCentroid() const = 0;

  virtual ~Object() {}
};
}
#endif
