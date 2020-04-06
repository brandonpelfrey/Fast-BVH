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
namespace impl {

//! \brief Node for storing state information during traversal.
template <typename Float>
struct Traversal final {
  //! The index of the node to be traversed.
  uint32_t i;

  //! Minimum hit time for this node.
  Float mint;

  //! Creates the traversal node for the root BVH node.
  inline static constexpr auto root() noexcept {
    return Traversal { 0, std::numeric_limits<Float>::infinity() };
  }
};

//! Used for traversing the BVH without using recursion.
template <typename Float>
class TraversalStack final {
  //! The queue of traversals.
  std::vector<Traversal<Float>> traversal_vec;
public:
  //! Constructs a new traversal stack.
  //! \param reserve_count The number of items to reserve memory for.
  TraversalStack(Size reserve_count = 0) {
    traversal_vec.reserve(reserve_count);
  }
  //! Queues an item for traversal.
  //! \tparam t The traversal to queue.
  inline void queue(const Traversal<Float>& t) {
    traversal_vec.emplace_back(t);
  }
  //! Removes an item from the stack to be used for traversal.
  inline auto pop() {
    auto last = traversal_vec[traversal_vec.size() - 1];
    traversal_vec.pop_back();
    return last;
  }
  //! Indicates the number of remaining items on the traversal stack.
  //! As long as this is non-zero, there is still traversal to be done.
  inline auto remaining() const noexcept {
    return traversal_vec.size();
  }
};

}  // namespace impl

template <typename Float, typename Primitive, typename Intersector, TraverserFlags Flags>
Intersection<Float, Primitive> Traverser<Float, Primitive, Intersector, Flags>::traverse(const Ray<Float>& ray) const {

  using Traversal = impl::Traversal<Float>;

  // Intersection result
  Intersection<Float, Primitive> intersection;

  // Bounding box min-t/max-t for left/right children at some point in the tree
  Float bbhits[4];
  uint32_t closer, other;

  impl::TraversalStack<Float> todo(64);

  todo.queue(Traversal::root());

  const auto nodes = bvh.getNodes();

  auto build_prims = bvh.getPrimitives();

  while (todo.remaining()) {

    // Pop off the next node to work on.
    auto traversal_node = todo.pop();
    const auto& node = nodes[traversal_node.i];
    auto near = traversal_node.mint;

    // If this node is further than the closest found intersection, continue
    if (near > intersection.t) {
      continue;
    }

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

      bool hitc0 = nodes[node.lower_node].bbox.intersect(ray, bbhits, bbhits + 1);
      bool hitc1 = nodes[node.upper_node].bbox.intersect(ray, bbhits + 2, bbhits + 3);

      // Did we hit both nodes?
      if (hitc0 && hitc1) {
        // We assume that the left child is a closer hit...
        closer = node.lower_node;
        other = node.upper_node;

        // ... If the right child was actually closer, swap the relavent values.
        if (bbhits[2] < bbhits[0]) {
          std::swap(bbhits[0], bbhits[2]);
          std::swap(bbhits[1], bbhits[3]);
          std::swap(closer, other);
        }

        // It's possible that the nearest object is still in the other side, but
        // we'll check the further-awar node later...

        // Push the farther first
        todo.queue(Traversal { other, bbhits[2] });

        // And now the closer (with overlap test)
        todo.queue(Traversal { closer, bbhits[0] });

      } else if (hitc0) {
        todo.queue(Traversal { node.lower_node, bbhits[0] });
      } else if (hitc1) {
        todo.queue(Traversal { node.upper_node, bbhits[2] });
      }
    }
  }

  return intersection;
}

}  // namespace FastBVH
