#pragma once

#include <FastBVH/BBox.h>

#include <FastBVH/impl/Array.h>

namespace FastBVH {

namespace impl {

//! \brief Used for computing a Morton space filling curve
//! to be used in the construction of a BVH.
//! \tparam Float The floating point type of the curve coordinates.
template <typename Float>
class MortonCurve final {
 public:
  //! A type definition for a Morton code.
  //! This is usually going to end up being a
  //! 32-bit or 64-bit unsigned integer.
  using Code = typename AssociatedIndexType<sizeof(Float)>::Type;

  //! A type definition for an array of Morton codes.
  using CodeArray = Array<Code>;

  //! Generates a series of Morton codes for a set of primitives.
  //! \tparam Primitive The type of the primitive to generate the codes for.
  //! \param primitives The array of primitives to generate the codes for.
  //! \param box_converter Used to convert the primitives into their bounding boxes.
  template <typename Primitive, typename BoxConverter>
  Array<Code> operator()(const ConstIterable<Primitive>& primitives, BoxConverter box_converter);

  //! Generates a Morton curve with a know minimum and maximum.
  //! This can be up to two times faster for situations in which the mininum
  //! and maximum values of scene are known.
  template <typename Primitive, typename BoxConverter>
  Array<Code> operator() (const ConstIterable<Primitive>& primitives, BoxConverter converter, const BBox<Float>& bbox);
};

} // namespace impl

} // namespace FastBVH

#include <FastBVH/impl/MortonCurve.inl>
