#pragma once

#include <FastBVH/BVH.h>

namespace FastBVH {

//! \brief Used for traversing a BVH
//! and checking for ray-primitive intersections.
//! \tparam Float The floating point type used by vector components.
//! \tparam Primitive The type of the primitive that the BVH was made with.
template <typename Float, typename Primitive>
class Traverser final {
  //! The BVH to be traversed.
  const BVH<Float, Primitive>& bvh;
public:
  //! Constructs a new BVH traverser.
  //! \param bvh_ The BVH to be traversed.
  constexpr Traverser(const BVH<Float, Primitive>& bvh_) noexcept
    : bvh(bvh_) {}
  //! Traces a single ray throughout the BVH, getting the closest intersection.
  //! \param ray The ray to be traced.
  //! \return An intersection instance.
  //! It may or may not be valid, based on whether or not the ray made a collision.
  Intersection<Float, Primitive> traverse(const Ray<Float>& ray, bool occlusion) const;
};

//! \brief Node for storing state information during traversal.
template <typename Float>
struct BVHTraversal final {
  //! The index of the node to be traversed.
  uint32_t i;
  //! Minimum hit time for this node.
  Float mint;
  //! Constructs an uninitialized instance of a traversal context.
  constexpr BVHTraversal() noexcept { }
  //! Constructs an initialized traversal context.
  //! \param i_ The index of the node to be traversed.
  constexpr BVHTraversal(int i_, Float mint_) noexcept
    : i(i_), mint(mint_) { }
};

template <typename Float, typename Primitive>
Intersection<Float, Primitive> Traverser<Float, Primitive>::traverse(const Ray<Float>& ray, bool occlusion) const {

  Intersection<Float, Primitive> intersection;

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
    if(near > intersection.t)
      continue;

    // Is leaf -> Intersect
    if( node.rightOffset == 0 ) {

      for(uint32_t o=0;o<node.nPrims;++o) {

        const auto& obj = build_prims[node.start + o];

        auto current = getPrimitiveIntersection(obj, ray);

        if (current) {
          // If we're only looking for occlusion, then any hit is good enough
          if(occlusion) {
            return current;
          }

          intersection = closest(intersection, current);
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
  if (intersection) {
    intersection.hit = ray.o + ray.d * intersection.t;
  }

  return intersection;
}

} // namespace FastBVH
