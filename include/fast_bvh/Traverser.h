#pragma once

#include <fast_bvh/BVH.h>

namespace FastBVH {

//! Used for traversing a BVH
//! and checking for ray-object
//! intersections.
template <typename Float>
class Traverser final {
  //! The BVH to be traversed.
  const BVH<Float>& bvh;
public:
  //! Constructs a new BVH traverser.
  //! \param bvh_ The BVH to be traversed.
  constexpr Traverser(const BVH<Float>& bvh_) noexcept
    : bvh(bvh_) {}
  //! Traces a single ray throughout the BVH, getting the closest intersection.
  //! \param ray The ray to be traced.
  //! \param intersection Receives the intersection info of the closest hit.
  //! \return True if the ray intersected a primitive, false otherwise.
  bool getIntersection(const Ray<Float>& ray, IntersectionInfo<Float> *intersection, bool occlusion) const;
};

//! Node for storing state information during traversal.
template <typename Float>
struct BVHTraversal final {
  uint32_t i; // Node
  Float mint; // Minimum hit time for this node.
  BVHTraversal() { }
  BVHTraversal(int _i, Float _mint) : i(_i), mint(_mint) { }
};

template <typename Float>
bool Traverser<Float>::getIntersection(const Ray<Float>& ray, IntersectionInfo<Float>* intersection, bool occlusion) const {

  intersection->t = 999999999.f;
  intersection->object = nullptr;

  Float bbhits[4];
  int32_t closer, other;

  // Working set
  BVHTraversal<Float> todo[64];
  int32_t stackptr = 0;

  // "Push" on the root node to the working set
  todo[stackptr].i = 0;
  todo[stackptr].mint = -9999999.f;

  const auto* flatTree = bvh.getNodes();

  const auto* build_prims = bvh.getPrimitives();

  while(stackptr>=0) {
    // Pop off the next node to work on.
    int ni = todo[stackptr].i;
    Float near = todo[stackptr].mint;
    stackptr--;
    const auto &node(flatTree[ ni ]);

    // If this node is further than the closest found intersection, continue
    if(near > intersection->t)
      continue;

    // Is leaf -> Intersect
    if( node.rightOffset == 0 ) {

      for(uint32_t o=0;o<node.nPrims;++o) {
        IntersectionInfo<Float> current;

        const auto* obj = build_prims[node.start+o];
        bool hit = obj->getIntersection(ray, &current);

        if (hit) {
          // If we're only looking for occlusion, then any hit is good enough
          if(occlusion) {
            return true;
          }

          // Otherwise, keep the closest intersection only
          if (current.t < intersection->t) {
            *intersection = current;
          }
        }
      }

    } else { // Not a leaf

      bool hitc0 = flatTree[ni+1].bbox.intersect(ray, bbhits, bbhits+1);
      bool hitc1 = flatTree[ni+node.rightOffset].bbox.intersect(ray, bbhits+2, bbhits+3);

      // Did we hit both nodes?
      if(hitc0 && hitc1) {

        // We assume that the left child is a closer hit...
        closer = ni+1;
        other = ni+node.rightOffset;

        // ... If the right child was actually closer, swap the relavent values.
        if(bbhits[2] < bbhits[0]) {
          std::swap(bbhits[0], bbhits[2]);
          std::swap(bbhits[1], bbhits[3]);
          std::swap(closer,other);
        }

        // It's possible that the nearest object is still in the other side, but we'll
        // check the further-awar node later...

        // Push the farther first
        todo[++stackptr] = BVHTraversal<Float>(other, bbhits[2]);

        // And now the closer (with overlap test)
        todo[++stackptr] = BVHTraversal<Float>(closer, bbhits[0]);
      }

      else if (hitc0) {
        todo[++stackptr] = BVHTraversal<Float>(ni+1, bbhits[0]);
      }

      else if(hitc1) {
        todo[++stackptr] = BVHTraversal<Float>(ni + node.rightOffset, bbhits[2]);
      }

    }
  }

  // If we hit something,
  if(intersection->object != NULL)
    intersection->hit = ray.o + ray.d * intersection->t;

  return intersection->object != NULL;
}

} // namespace FastBVH
