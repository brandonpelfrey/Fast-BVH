#pragma once

#include <FastBVH/Vector3.h>

#include <random>

namespace FastBVH {

namespace Testing {

//! \brief This is a primitive suitable for testing.
template <typename Float>
struct Primitive final {
  //! The minimum point of the test primitive.
  Vector3<Float> min;

  //! The maximum point of the test primitive.
  Vector3<Float> max;
};

//! \brief Used for converting test primitives
//! to bounding boxes.
template <typename Float>
class BoxConverter final {
 public:
  //! Converts a test primitive to a bounding box.
  //! \param p The test primitive to convert.
  //! \return A bounding box that encapsulates the test primitive.
  BBox<Float> operator()(const Primitive<Float>& p) const noexcept { return BBox<Float>(p.min, p.max); }
};

}  // namespace Testing

}  // namespace FastBVH
