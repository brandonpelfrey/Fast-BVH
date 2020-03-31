#pragma once

#include "Rng.h"

namespace FastBVH {

namespace benchmark {

//! \brief An array of 3D vectors, in SoA format.
//! \tparam Float The floating point type of the vector components.
template <typename Float>
struct VectorArray final {
  //! The X value array.
  Array<Float> x;

  //! The Y value array.
  Array<Float> y;

  //! The Z value array.
  Array<Float> z;

  //! Allocates a new vector array.
  //! \param count The number of values to allocate.
  static auto make(Size count) {
    return VectorArray<Float> {
      count, count, count
    };
  }

  //! Generates a randomized vector array.
  //! \param count The number of vectors to put into the array.
  //! This is also used as the min and max of the values.
  static auto random(Size count) {

    Rng<Float> rng;

    return VectorArray<Float> {
      rng(-Float(count), Float(count), count),
      rng(-Float(count), Float(count), count),
      rng(-Float(count), Float(count), count)
    };
  }
};

//! \brief An array of boxes, used for benchmarking.
//! \tparam Float The floating point type of the box vectors.
template <typename Float>
struct BoxArray final {

  //! \brief The array of minimum values for each box.
  VectorArray<Float> min;

  //! \brief The array of maximum values for each box.
  VectorArray<Float> max;

  //! \brief A type definition for a box index.
  using Index = typename AssociatedIndexType<sizeof(Float)>::Type;

  //! \brief A type definition for an array of box indices.
  using Indices = Array<Index>;

  //! \brief Generates a box array with randomized values.
  //! \param count The number of boxes to generate.
  //! \return A box array with randomized positions.
  static BoxArray<Float> random(Size count);

  //! \brief Creates an array of indices for each of the boxes.
  //! This is used to index the box array with a box converter.
  Indices makeIndices();
};

} // namespace benchmark

} // namespace FastBVH

#include "BoxArray.inl"
