#include <FastBVH/BBox.h>

#include <FastBVH/impl/MortonCurve.h>

#include "BoxArray.h"

#include "../examples/Stopwatch.h"

#include <cstdio>

namespace {

using namespace FastBVH;

//! \brief Runs the benchmark for a single type.
//! \tparam Float The floating point type to use for the benchmark.
template <typename Float>
void runBenchmark() {

  using Index = typename AssociatedIndexType<sizeof(Float)>::Type;

  constexpr auto float_bits = sizeof(Float) * 8;

  std::printf("Running Morton curve benchmark (%u-bit floats)\n", (unsigned int) float_bits);

  std::printf("  Generating random boxes\n");

  constexpr Size box_count = 1'000'000;

  auto rand_boxes = benchmark::BoxArray<Float>::random(box_count);

  auto box_converter = [&rand_boxes](Index box) {

    Vector3<Float> min {
      rand_boxes.min.x[box],
      rand_boxes.min.y[box],
      rand_boxes.min.z[box]
    };

    Vector3<Float> max {
      rand_boxes.max.x[box],
      rand_boxes.max.y[box],
      rand_boxes.max.z[box]
    };

    return BBox<Float>(min, max);
  };

  std::printf("  Calculating Morton curve\n");

  auto box_indices = rand_boxes.makeIndices();

  Vector3<Float> scene_min {
    -Float(box_count),
    -Float(box_count),
    -Float(box_count),
  };

  Vector3<Float> scene_max {
    Float(box_count + 1),
    Float(box_count + 1),
    Float(box_count + 1),
  };

  BBox<Float> scene_bbox(scene_min, scene_max);

  Stopwatch stopwatch;

  impl::MortonCurve<Float> morton_curve;

  auto codes = morton_curve(box_indices.getConstElements(), box_converter, scene_bbox);

  auto time = stopwatch.read();

  std::printf("  Completed in %06.04f seconds\n", time);

  (void)codes;
}

} // namespace

int main() {
  runBenchmark<float>();
  runBenchmark<double>();
#ifndef FASTBVH_NO_INT128
  runBenchmark<long double>();
#endif // FASTBVH_NO_INT128
  return 0;
}
