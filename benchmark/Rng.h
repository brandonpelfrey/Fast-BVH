#pragma once

#include <FastBVH/impl/Array.h>

#include <random>

#include <stdexcept>

namespace FastBVH {

namespace benchmark {

//! \brief A type definition for arrays.
//! Here we use the array class in @ref FastBVH::impl,
//! since it's always allocated in the right memory space.
template <typename T>
using Array = impl::Array<T>;

//! \brief Generates a set of random numbers.
//! \tparam Float The floating point type to generate random numbers with.
template <typename Float>
class Rng final {
public:
  //! \param min The minimum value of the distribution.
  //! \param max The minimum value of the distribution.
  //! \param count The number of random values to generate.
  Array<Float> operator () (Float min, Float max, Size count);
};

template <typename Float>
Array<Float> Rng<Float>::operator () (Float min, Float max, Size count) {

  Array<Float> output_array(count);

  std::random_device device;

  std::default_random_engine rng(device());

  std::uniform_real_distribution<Float> dist(min, max);

  for (Size i = 0; i < count; i++) {
    output_array[i] = dist(device);
  }

  return output_array;
}

} // namespace benchmark

} // namespace FastBVH
