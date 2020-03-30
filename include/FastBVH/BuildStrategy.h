#pragma once

#include <FastBVH/BVH.h>
#include <FastBVH/Config.h>

#ifdef FASTBVH_NO_STL
#include <vector>
#endif

namespace FastBVH {

//! \brief This is the interface for the algorithm
//! that is used to construct a BVH. There are many
//! BVH construction algorithms, with different trade-offs.
//! This class allows many different algorithms to have
//! the same interface, so that they can be used in place
//! of one another, depending on the use case.
//!
//! The default behavior of this class is to store all the
//! primitives in the root node. Derived strategy classes
//! contain the useful algorithms. The implementation in the
//! base class is more of a placeholder than anything else.
//!
//! \tparam variant The variant of the build strategy.
//! Variant zero is the default build strategy.
template <typename Float, int variant>
class BuildStrategy final {
 public:
  //! Builds an extremely primitive BVH.
  //! \tparam Primitive The type of primitive the BVH is being built for.
  //! \tparam BoxConverter The type of the primitive-to-box converter.
  //! \param primitives The array of primitives to build the BVH for.
  //! \param converter The primitive-to-box converter instance.
  template <typename Primitive, typename BoxConverter>
  auto operator()(Iterable<Primitive> primitives, BoxConverter converter) {
    Vector3<Float> init_min{std::numeric_limits<Float>::infinity(), std::numeric_limits<Float>::infinity(),
                            std::numeric_limits<Float>::infinity()};

    Vector3<Float> init_max{-std::numeric_limits<Float>::infinity(), -std::numeric_limits<Float>::infinity(),
                            -std::numeric_limits<Float>::infinity()};

    BBox<Float> bbox(init_min, init_max);

    for (const auto& p : primitives) {
      bbox.expandToInclude(converter(p));
    }

    Node<Float> root_node{
        bbox, 0 /* primitives start index */, (uint32_t)primitives.size(),
        0 /* right offset (0 indicates no sub-nodes) */
    };

    NodeArray<Float> nodes;

    nodes.emplace_back(root_node);

    return BVH<Float, Primitive>(std::move(nodes), primitives);
  }

#ifndef FASTBVH_NO_STL
  //! This is a function that takes a STL vector of primitives,
  //! instead of the @ref Iterable container.
  template <typename Primitive, typename BoxConverter>
  BVH<Float, Primitive> operator()(std::vector<Primitive>& primitives, BoxConverter converter) {
    Iterable<Primitive> iterable(primitives.data(), primitives.size());

    return (*this)(iterable, converter);
  }
#endif
};

//! This is the first variant build strategy.
//! It is a single threaded BVH builder.
template <typename Float>
class BuildStrategy<Float, 1> final {
 public:
  //! Builds a BVH using the original algorithm.
  template <typename Primitive, typename BoxConverter>
  BVH<Float, Primitive> operator()(Iterable<Primitive> primitives, BoxConverter converter);

#ifndef FASTBVH_NO_STL
  //! This is a function that takes a STL vector of primitives,
  //! instead of the @ref Iterable container.
  template <typename Primitive, typename BoxConverter>
  BVH<Float, Primitive> operator()(std::vector<Primitive>& primitives, BoxConverter converter) {
    Iterable<Primitive> iterable(primitives.data(), primitives.size());

    return (*this)(iterable, converter);
  }
#endif
};

//! This is the type definition for the default build strategy.
//! The default is the original algorithm used for BVH construction.
template <typename Float>
using DefaultBuilder = BuildStrategy<Float, 1>;

}  // namespace FastBVH
