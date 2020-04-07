#pragma once

#include <FastBVH/BuildStrategy.h>

#include <FastBVH/impl/MortonCurve.h>

namespace FastBVH {

namespace impl {

//! \brief Contains the implementation details
//! for build strategy #2.
namespace strategy_2 {

//! \brief Represents the division of an internal node.
struct NodeDiv final {
  //! The index of the beginning of the node range.
  Size begin;

  //! The index of the ending of the node range.
  //! The ranges are not bounded, so this index is inclusive.
  Size end;

  //! The index at which the node should be split.
  Size split;

  //! Gets the minimum index of the range.
  inline constexpr auto min() const noexcept {
    return (begin < end) ? begin : end;
  }

  //! Gets the maximum index of the range.
  inline constexpr auto max() const noexcept {
    return (end > begin) ? end : begin;
  }
};

//! \brief Divides a node into two ranges.
//!
//! This is the function described in pseudocode
//! by Karras at: https://devblogs.nvidia.com/wp-content/uploads/2012/11/karras2012hpg_paper.pdf
//!
//! \tparam Code The type of one Morton code.
//!
//! \param table The table of sorted Morton codes.
//! \param i The index of the node to divide.
//! \return The division structure for the node.
template <typename Code>
NodeDiv divideNode(const MortonTable<Code>& table, Size i) noexcept {

  // Calculates upper bits, or returns -1
  // if 'k' is out of bounds. Appears in the
  // LBVH paper as 'δ' (lower case delta)
  auto calc_delta = [&table](int j, int k) -> int {

    if ((k < 0) || (k >= int(table.size()))) {
      return -1;
    }

    auto l_code = table[j];
    auto r_code = table[k];

    if (l_code == r_code) {
      return clz(j ^ k) + (sizeof(Code) * 8);
    } else {
      return clz(l_code ^ r_code);
    }
  };

  auto ceilDiv = [](int n, int d) {
    return (n / d) + ((n % d) ? 1 : 0);
  };

  auto min = [](int a, int b) {
    return (a < b) ? a : b;
  };

  int d = calc_delta(i, i + 1)
        - calc_delta(i, i - 1);

  d = d < 0 ? -1 : 1;

  int delta_min = calc_delta(i, i - d);

  int l_max = 2;

  while (true) {

    int k = i + (l_max * d);

    if (k >= int(table.size())) {
      break;
    }

    if (!(calc_delta(i, k) > delta_min)) {
      break;
    }

    l_max *= 2;
  }

  int l = 0;

  for (int div = 2; true; div *= 2) {

    int t = l_max / div;

    int k = i + ((l + t) * d);

    if (calc_delta(i, k) > delta_min) {
      l += t;
    }

    if (t == 1) {
      break;
    }
  }

  int j = i + (l * d);

  int delta_node = calc_delta(i, j);

  int s = 0;

  for (int div = 2; true; div *= 2) {

    int t = ceilDiv(l, div);

    int k = i + ((s + t) * d);

    if (calc_delta(i, k) > delta_node) {
      s += t;
    }

    if (div >= l) {
      break;
    }
  }

  int gamma = i + (s * d) + min(d, 0);

  return NodeDiv {
    Size(i),
    Size(j),
    Size(gamma)
  };
}

//! This function is used to calculate the bounding
//! boxes to assign each internal node.
//!
//! \tparam Float The floating point type of the boxes.
//!
//! \param nodes The node array to fit the boxes for.
//! It's expected that the internal nodes (the ones after @p inode_count)
//! already have bounding boxes assigned to them that are correct.
//!
//! \param inode_count The number of internal nodes to assign bounding boxes to.
template <typename Float>
void fitBoxes(NodeArray<Float>& nodes, Size inode_count) {

  std::vector<Size> indices;

  indices.reserve(inode_count);

  indices.push_back(0);

  for (Size i = 0; (i < indices.size()) && (i < inode_count); i++) {

    auto index = indices[i];

    if (nodes[index].isLeaf()) {
      continue;
    }

    auto& lower = nodes[nodes[index].lower_node];
    if (!lower.isLeaf()) {
      indices.push_back(nodes[index].lower_node);
    }

    auto& upper = nodes[nodes[index].upper_node];
    if (!upper.isLeaf()) {
      indices.push_back(nodes[index].upper_node);
    }
  }

  for (Size i = indices.size(); i > 0; i--) {

    auto& node = nodes[indices[i - 1]];

    node.bbox = nodes[node.lower_node].bbox;

    node.bbox.expandToInclude(nodes[node.upper_node].bbox);
  }
}

} // namespace strategy_2

} // namespace impl

template <typename Float>
template <typename Primitive, typename BoxConverter>
BVH<Float, Primitive> BuildStrategy<Float, 2>::operator()(Iterable<Primitive> primitives, BoxConverter converter) {

  using namespace impl;
  using namespace impl::strategy_2;

  MortonCurve<Float> morton_curve;

  auto morton_codes = morton_curve(ConstIterable<Primitive>(primitives), converter);

  morton_codes.sort();

  NodeArray<Float> nodes((primitives.size() * 2) - 1);

  // The number of internal nodes (non-leaf nodes.)
  auto inode_count = primitives.size() - 1;

  for (Size i = inode_count; i < nodes.size(); i++) {
    nodes[i].lower_node = 0;
    nodes[i].upper_node = 0;
    nodes[i].start = morton_codes.getPrimitive(i - inode_count);
    nodes[i].primitive_count = 1;
    nodes[i].bbox = converter(primitives[nodes[i].start]);
  }

  for (Size i = 0; i < inode_count; i++) {

    auto node_div = divideNode(morton_codes, i);

    nodes[i].primitive_count = 0;
    nodes[i].start = 0;
    nodes[i].lower_node = node_div.split;
    nodes[i].upper_node = node_div.split + 1;

    if (node_div.min() == node_div.split) {
      nodes[i].lower_node += inode_count;
    }

    if (node_div.max() == (node_div.split + 1)) {
      nodes[i].upper_node += inode_count;
    }
  }

  fitBoxes(nodes, inode_count);

  return BVH<Float, Primitive>(std::move(nodes), primitives);
}

}  // namespace FastBVH
