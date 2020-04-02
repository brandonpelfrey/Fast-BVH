#include <FastBVH/impl/MortonCurve.h>

using namespace FastBVH;
using namespace FastBVH::impl;

Array<U32> generateMorton32(const float* vertices_x,
                            const float* vertices_y,
                            const float* vertices_z,
                            const int* spheres,
                            Size count) {

  auto sphereToBox = [vertices_x, vertices_y, vertices_z](int s) {

    Vector3<float> min {
      vertices_x[s] - 0.5f,
      vertices_y[s] - 0.5f,
      vertices_z[s] - 0.5f
    };

    Vector3<float> max {
      vertices_x[s] + 0.5f,
      vertices_y[s] + 0.5f,
      vertices_z[s] + 0.5f
    };

    return BBox<float>(min, max);
  };

  MortonCurve<float> curve;

  Vector3<float> scene_min {
    -512,
    -512,
    -512
  };

  Vector3<float> scene_max {
    512,
    512,
    512
  };

  BBox<float> scene_bbox(scene_min, scene_max);

  return curve(ConstIterable<int>(spheres, count), sphereToBox, scene_bbox);
}
