#include <FastBVH/BuildStrategy.h>

namespace FastBVH {

//! \brief Contains details on the implementation
//! of the variant-1 BVH build strategy.
namespace Strategy1 {

//! \brief Contains the context used while building
//! a specific node in the BVH.
struct BuildEntry final {
  //! If non-zero then this is the index of the parent. (used in offsets)
  uint32_t parent;

  //! The starting index of the range of primitives in this node.
  uint32_t start;

  //! The ending index of the range of primitives in this node.
  uint32_t end;
};

//! \brief Used while constructing the BVH
//! to queue nodes to be built.
class BuildStack final {
  //! The maximum number of entries in the stack.
  static constexpr std::size_t max_size = 128;

  //! The entry array of the stack.
  BuildEntry entries[max_size];

  //! The index of the current entry, plus one.
  //! A value of zero indicates an empty stack.
  std::size_t stack_ptr = 0;

 public:
  //! Pops the top entry from the stack.
  //! This function does not check if the
  //! stack is empty.
  auto pop() noexcept { return entries[--stack_ptr]; }

  //! Pushes an entry to the stack.
  //! \param entry The entry to be pushed.
  void push(const BuildEntry& entry) noexcept {
    entries[stack_ptr] = entry;
    stack_ptr++;
  }

  //! Indicates the size of the stack.
  //! \return The number of entries in the stack.
  //! A value of zero indicates the stack is empty.
  auto size() const noexcept { return stack_ptr; }

  //! Accesses an entry from the stack, by index.
  //! \param index The index of the entry to get.
  //! This is not a top-down index, so an index of
  //! zero would reference the first item added to the stack.
  //! \return A reference to the specified entry.
  const auto& operator[](std::size_t index) const noexcept { return entries[index]; }
};

}  // namespace Strategy1

template <typename Float>
template <typename Primitive, typename BoxConverter>
BVH<Float, Primitive> BuildStrategy<Float, 1>::operator()(Iterable<Primitive> primitives, BoxConverter converter) {
  using namespace Strategy1;

  // The threshold hold at which a leaf is made in the BVH.
  static constexpr uint32_t leaf_size = 4;

  BuildStack todo;

  const uint32_t Untouched = 0xffffffff;
  const uint32_t TouchedTwice = 0xfffffffd;
  uint32_t node_count = 0;

  // Push the root
  BuildEntry root{
      0xfffffffc /* parent */,
      0 /* start */,
      (uint32_t)primitives.size() /* end */
  };

  todo.push(root);

  Node<Float> node;
  std::vector<Node<Float>> build_nodes;
  build_nodes.reserve(primitives.size() * 2);

  while (todo.size() > 0) {
    auto bnode = todo.pop();

    uint32_t start = bnode.start;
    uint32_t end = bnode.end;
    uint32_t primitive_count = end - start;

    node_count++;
    node.start = start;
    node.primitive_count = primitive_count;
    node.right_offset = Untouched;

    // Calculate the bounding box for this node
    auto bb = converter(primitives[start]);
    auto bc = BBox<Float>(bb.getCenter());

    for (uint32_t p = start + 1; p < end; ++p) {
      auto box = converter(primitives[p]);
      bb.expandToInclude(box);
      bc.expandToInclude(box.getCenter());
    }

    node.bbox = bb;

    // If the number of primitives at this point is less than the leaf
    // size, then this will become a leaf. (Signified by right_offset == 0)
    if (primitive_count <= leaf_size) {
      node.right_offset = 0;
    }

    build_nodes.push_back(node);

    // Child touches parent...
    // Special case: Don't do this for the root.
    if (bnode.parent != 0xfffffffc) {
      build_nodes[bnode.parent].right_offset--;

      // When this is the second touch, this is the right child.
      // The right child sets up the offset for the flat tree.
      if (build_nodes[bnode.parent].right_offset == TouchedTwice) {
        build_nodes[bnode.parent].right_offset = node_count - 1 - bnode.parent;
      }
    }

    // If this is a leaf, no need to subdivide.
    if (node.right_offset == 0) continue;

    // Set the split dimensions
    uint32_t split_dim = bc.maxDimension();

    // Split on the center of the longest axis
    Float split_coord = .5f * (bc.min[split_dim] + bc.max[split_dim]);

    // Partition the list of objects on this split
    uint32_t mid = start;
    for (uint32_t i = start; i < end; ++i) {
      auto box = converter(primitives[i]);
      if (box.getCenter()[split_dim] < split_coord) {
        std::swap(primitives[i], primitives[mid]);
        ++mid;
      }
    }

    // If we get a bad split, just choose the center...
    if (mid == start || mid == end) {
      mid = start + (end - start) / 2;
    }

    BuildEntry right_child{node_count - 1, mid, end};

    BuildEntry left_child{node_count - 1, start, mid};

    todo.push(right_child);
    todo.push(left_child);
  }

  NodeArray<Float> nodes;

  nodes.resize(node_count);

  for (uint32_t n = 0; n < node_count; n++) {
    nodes[n] = build_nodes[n];
  }

  return BVH<Float, Primitive>(std::move(nodes), primitives);
}

}  // namespace FastBVH
