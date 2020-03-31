#pragma once

#include <FastBVH/impl/MortonCodec.h>
#include <FastBVH/impl/MortonCurve.h>
#include <FastBVH/impl/MortonTraits.h>
#include <FastBVH/impl/VectorPacket.h>

#include <limits>

namespace FastBVH {

namespace impl {

template <typename Float>
template <typename Primitive, typename BoxConverter>
auto MortonCurve<Float>::operator()(const ConstIterable<Primitive>& primitives, BoxConverter box_converter) -> Output {

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
auto MortonCurve<Float>::operator() (const ConstIterable<Primitive>& primitives, BoxConverter converter, const BBox<Float>& bbox) -> Output {

  // This is the domain of the scene.
  // In other words, the maximum distance
  // between two primitives.
  auto domain = bbox.extent;

  // This is the domain of "Morton space".
  // It's [0, 1024) for 32-bit floats, and higher
  // for double or long double.
  constexpr auto morton_domain = MortonTraits<sizeof(Float)>::domain();

  // This is the scale at which the center points
  // of the primitives are multiplied by in order
  // to be transformed into "Morton space".
  Vector3<Float> scale {
    morton_domain / domain.x,
    morton_domain / domain.y,
    morton_domain / domain.z
  };

  // The Morton codes get put into here.
  MortonTable<Code> codes(primitives.size());

  // Used to convert a 3D point into a Morton code.
  MortonEncoder<sizeof(Float)> codec;

  // This is defined in '<algorithm>' but definining
  // it here keeps the compile times low.
  auto min = [](auto a, auto b) { return (a < b) ? a : b; };

  // This loop uses arrays.
  // Three of the rays are for the center points axes.
  // A last array is for the code values.
  //
  // Therefore, we'll be using one fourth of the cache
  // per component.
  constexpr auto cache_lines = cacheLinesPerL1() / 4;

  // This is the number of points we'll be processing at a time.
  constexpr auto batch_size_max = VectorPacket<Float, 3, cache_lines>::size();

  // Contains all the center points to be processed at at time.
  VectorPacket<Float, 3, cache_lines> center;

  alignas(cacheLineSize()) Code batch_codes[batch_size_max];

  auto count = primitives.size();

  for (decltype(count) i = 0; i < count; i += batch_size_max) {

    auto batch_size = ((i + batch_size_max) < count) ? batch_size_max : (count - i);

    // Load center values from primitives into the batch.
    for (decltype(batch_size) j = 0; j < batch_size; j++) {
      auto pc = converter(primitives[i + j]).getCenter();
      center[0][j] = pc.x;
      center[1][j] = pc.y;
      center[2][j] = pc.z;
    }

    center = hadamard(center - bbox.min, scale);

    // Process center values in batch.
    for (decltype(batch_size) j = 0; j < batch_size; j++) {

      Code x_code = Code(center[0][j]);
      Code y_code = Code(center[1][j]);
      Code z_code = Code(center[2][j]);

      x_code = min(x_code, morton_domain - 1);
      y_code = min(y_code, morton_domain - 1);
      z_code = min(z_code, morton_domain - 1);

      batch_codes[j] = codec(x_code, y_code, z_code);
    }

    // Unload code values from batch into destination array.
    for (decltype(batch_size) j = 0; j < batch_size; j++) {
      codes.initCode(i + j, batch_codes[j]);
    }
  }

  return codes;
}

} // namespace impl

} // namespace FastBVH
