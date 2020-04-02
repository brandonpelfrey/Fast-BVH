#pragma once

#include "BoxArray.h"

namespace FastBVH {

namespace benchmark {

template <typename Float>
BoxArray<Float> BoxArray<Float>::random(Size count) {

  BoxArray<Float> box_array {
    VectorArray<Float>::random(count),
    VectorArray<Float>::make(count)
  };

  for (Size i = 0; i < count; i++) {
    box_array.max.x[i] = box_array.min.x[i] + Float(1);
    box_array.max.y[i] = box_array.min.y[i] + Float(1);
    box_array.max.z[i] = box_array.min.z[i] + Float(1);
  }

  return box_array;
}

template <typename Float>
typename BoxArray<Float>::Indices BoxArray<Float>::makeIndices() {

  auto max = Index(min.x.size());

  Array<Index> indices(max);

  for (Index i = 0; i < max; i++) {
    indices[i] = i;
  }

  return indices;
}

} // namespace benchmark

} // namespace FastBVH
