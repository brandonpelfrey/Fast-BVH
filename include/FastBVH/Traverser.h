#pragma once

#include <FastBVH/BVH.h>

namespace FastBVH {

//! \brief Flags used to configure traverse() method of the BVH.
enum TraverserFlags {
  //! If any intersection exists, return immediately. The Intersection data is not populated.
  OnlyTestOcclusion = 1 << 0,
};

//! \brief Used for traversing a BVH and checking for ray-primitive intersections.
//! \tparam Float The floating point type used by vector components.
//! \tparam Primitive The type of the primitive that the BVH was made with.
//! \tparam Intersector The type of the primitive intersector.
//! \tparam Flags The flags which configure traversal. See @ref TraverserFlags. By default, no flags are active.
template <typename Float, typename Primitive, typename Intersector, TraverserFlags Flags = TraverserFlags(0)>
class Traverser final {
  //! The BVH to be traversed.
  const BVH<Float, Primitive>& bvh;

  /// The ray-primitive intersector.
  Intersector intersector;

 public:
  //! Constructs a new BVH traverser.
  //! \param bvh_ The BVH to be traversed.
  constexpr Traverser(const BVH<Float, Primitive>& bvh_, const Intersector& intersector_) noexcept
      : bvh(bvh_), intersector(intersector_) {}
  //! Traces a single ray throughout the BVH, getting the closest intersection.
  //! \param ray The ray to be traced.
  //! \return An intersection instance.
  //! It may or may not be valid, based on whether or not the ray made a collision.
  Intersection<Float, Primitive> traverse(const Ray<Float>& ray) const;
};

//! \brief Contains implementation details for the @ref Traverser class.
namespace TraverserImpl {

//! \brief Node for storing state information during traversal.
template <typename Float>
struct Traversal final {
  //! The index of the node to be traversed.
  uint32_t i;

  //! Minimum hit time for this node.
  Float mint;

  //! Constructs an uninitialized instance of a traversal context.
  constexpr Traversal() noexcept {}

  //! Constructs an initialized traversal context.
  //! \param i_ The index of the node to be traversed.
  constexpr Traversal(int i_, Float mint_) noexcept : i(i_), mint(mint_) {}
};

}  // namespace TraverserImpl

template <typename Float, typename Primitive, typename Intersector, TraverserFlags Flags>
Intersection<Float, Primitive> Traverser<Float, Primitive, Intersector, Flags>::traverse(const Ray<Float>& ray) const {
  using Traversal = TraverserImpl::Traversal<Float>;

  // Intersection result
  Intersection<Float, Primitive> intersection;

  // Bounding box min-t/max-t for left/right children at some point in the tree
  Float bbhits[4];
  int32_t closer, other;

  // Working set
  // WARNING : The working set size is relatively small here, should be made dynamic or template-configurable
  Traversal todo[64];
  int32_t stackptr = 0;

  // "Push" on the root node to the working set
  todo[stackptr].i = 0;
  todo[stackptr].mint = -9999999.f;

  const auto nodes = bvh.getNodes();

  auto build_prims = bvh.getPrimitives();

  while (stackptr >= 0) {
    // Pop off the next node to work on.
    int ni = todo[stackptr].i;
    Float near = todo[stackptr].mint;
    stackptr--;
    const auto& node(nodes[ni]);

    // If this node is further than the closest found intersection, continue
    if (near > intersection.t) continue;

    // Is leaf -> Intersect
    if (node.isLeaf()) {
      for (uint32_t o = 0; o < node.primitive_count; ++o) {
        const auto& obj = build_prims[node.start + o];

        auto current = intersector(obj, ray);
        if (current) {
          // If we're only looking for occlusion, then any hit is good enough to return true
          if (Flags & TraverserFlags::OnlyTestOcclusion) {
            return current;
          }
          intersection = closest(intersection, current);
        }
      }

    } else {  // Not a leaf

      bool hitc0 = nodes[ni + 1].bbox.intersect(ray, bbhits, bbhits + 1);
      bool hitc1 = nodes[ni + node.right_offset].bbox.intersect(ray, bbhits + 2, bbhits + 3);

      // Did we hit both nodes?
      if (hitc0 && hitc1) {
        // We assume that the left child is a closer hit...
        closer = ni + 1;
        other = ni + node.right_offset;

        // ... If the right child was actually closer, swap the relavent values.
        if (bbhits[2] < bbhits[0]) {
          std::swap(bbhits[0], bbhits[2]);
          std::swap(bbhits[1], bbhits[3]);
          std::swap(closer, other);
        }

        // It's possible that the nearest object is still in the other side, but
        // we'll check the further-awar node later...

        // Push the farther first
        todo[++stackptr] = Traversal(other, bbhits[2]);

        // And now the closer (with overlap test)
        todo[++stackptr] = Traversal(closer, bbhits[0]);
      }

      else if (hitc0) {
        todo[++stackptr] = Traversal(ni + 1, bbhits[0]);
      }

      else if (hitc1) {
        todo[++stackptr] = Traversal(ni + node.right_offset, bbhits[2]);
      }
    }
  }

  return intersection;
}

}  // namespace FastBVH
