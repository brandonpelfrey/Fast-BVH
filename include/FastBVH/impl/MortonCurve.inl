#pragma once

#include <FastBVH/impl/MortonCodec.h>
#include <FastBVH/impl/MortonCurve.h>
#include <FastBVH/impl/MortonTraits.h>

#include <limits>

namespace FastBVH {

namespace impl {

template <typename Float>
template <typename Primitive, typename BoxConverter>
typename MortonCurve<Float>::CodeArray MortonCurve<Float>::operator()(const ConstIterable<Primitive>& primitives, BoxConverter box_converter) {

  Vector3<Float> center_min = {std::numeric_limits<Float>::infinity(), std::numeric_limits<Float>::infinity(),
                               std::numeric_limits<Float>::infinity()};

  Vector3<Float> center_max = {-std::numeric_limits<Float>::infinity(), -std::numeric_limits<Float>::infinity(),
                               -std::numeric_limits<Float>::infinity()};

  auto count = primitives.size();

  for (decltype(count) i = 0; i < count; i++) {
    auto box = box_converter(primitives[i]);
    auto center = box.getCenter();
    center_min = min(center_min, center);
    center_max = max(center_max, center);
  }

  BBox<Float> bbox(center_min, center_max);

  return (*this)(primitives, box_converter, bbox);
}

template <typename Float>
template <typename Primitive, typename BoxConverter>
typename MortonCurve<Float>::CodeArray MortonCurve<Float>::operator() (const ConstIterable<Primitive>& primitives, BoxConverter converter, const BBox<Float>& bbox) {

  auto domain = bbox.extent;

  auto morton_domain = MortonTraits<sizeof(Float)>::domain();

  auto x_factor = morton_domain / domain.x;
  auto y_factor = morton_domain / domain.y;
  auto z_factor = morton_domain / domain.z;

  Array<Code> codes(primitives.size());

  MortonEncoder<sizeof(Float)> codec;

  auto min = [](auto a, auto b) { return (a < b) ? a : b; };

  auto count = primitives.size();

  // This is the number of floating point values
  // per axis that we'll process at a time. The idea
  // to the calculation is that we want to process as
  // many values that will fit into 1K of stack memory.
  // This encourages vectorization while also being cache friendly.
  constexpr Size batch_size_max = 1024 / sizeof(Float);

  // 64-byte alignment gives us good alignment
  // all the way up to 16-lane SIMD tech, such as AVX-512
  alignas(64) Float center_x[batch_size_max];
  alignas(64) Float center_y[batch_size_max];
  alignas(64) Float center_z[batch_size_max];
  alignas(64) Code batch_codes[batch_size_max];

  for (decltype(count) i = 0; i < count; i += batch_size_max) {

    auto batch_size = ((i + batch_size_max) < count) ? batch_size_max : (count - i);

    // Load center values from primitives into the batch.
    for (decltype(batch_size) j = 0; j < batch_size; j++) {
      auto pc = converter(primitives[i + j]).getCenter();
      center_x[j] = pc.x;
      center_y[j] = pc.y;
      center_z[j] = pc.z;
    }

    // Process center values in batch.
    for (decltype(batch_size) j = 0; j < batch_size; j++) {

      center_x[j] = (center_x[j] - bbox.min.x) * x_factor;
      center_y[j] = (center_y[j] - bbox.min.y) * y_factor;
      center_z[j] = (center_z[j] - bbox.min.z) * z_factor;

      Code x_code = Code(center_x[j]);
      Code y_code = Code(center_y[j]);
      Code z_code = Code(center_z[j]);

      x_code = min(x_code, morton_domain - 1);
      y_code = min(y_code, morton_domain - 1);
      z_code = min(z_code, morton_domain - 1);

      batch_codes[j] = codec(x_code, y_code, z_code);
    }

    // Unload code values from batch into destination array.
    for (decltype(batch_size) j = 0; j < batch_size; j++) {
      codes[i + j] = batch_codes[j];
    }
  }

  return codes;
}

} // namespace impl

} // namespace FastBVH
