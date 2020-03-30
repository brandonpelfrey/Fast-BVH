#pragma once

#include <FastBVH/BBox.h>

#include <vector>

#include "../examples/tiny_obj_loader.h"

namespace FastBVH {

namespace Benchmark {

//! \brief Converts a face into a bounding box.
//! Used by @ref FaceBVH::BVH during the build process.
class FaceBoxConverter final {
  /// The minimum X values of the mesh faces.
  std::vector<float> min_x;

  /// The minimum Y values of the mesh faces.
  std::vector<float> min_y;

  /// The minimum Z values of the mesh faces.
  std::vector<float> min_z;

  /// The maximum X values of the mesh faces.
  std::vector<float> max_x;

  /// The maximum Y values of the mesh faces.
  std::vector<float> max_y;

  /// The maximum Z values of the mesh faces.
  std::vector<float> max_z;

 public:
  //! Constructs a new instance of the box converter.
  //! \param attrib Used to resolve the face indices
  //! into points that can be used to determine the
  //! bounding box of a face.
  //! \param faces The faces of the mesh.
  FaceBoxConverter(const tinyobj::attrib_t& attrib, const std::vector<Face>& faces) {

    min_x.resize(faces.size());
    min_y.resize(faces.size());
    min_z.resize(faces.size());

    max_x.resize(faces.size());
    max_y.resize(faces.size());
    max_z.resize(faces.size());

    for (std::size_t i = 0; i < faces.size(); i++) {
      const auto& face = faces[i];

      FastBVH::Vector3<float> pos_a = {attrib.vertices[(face.pos[0] * 3) + 0], attrib.vertices[(face.pos[0] * 3) + 1],
                                       attrib.vertices[(face.pos[0] * 3) + 2]};

      FastBVH::Vector3<float> pos_b = {attrib.vertices[(face.pos[1] * 3) + 0], attrib.vertices[(face.pos[1] * 3) + 1],
                                       attrib.vertices[(face.pos[1] * 3) + 2]};

      FastBVH::Vector3<float> pos_c = {attrib.vertices[(face.pos[2] * 3) + 0], attrib.vertices[(face.pos[2] * 3) + 1],
                                       attrib.vertices[(face.pos[2] * 3) + 2]};

      auto min = FastBVH::min(pos_a, pos_b);
      auto max = FastBVH::max(pos_a, pos_b);

      min = FastBVH::min(min, pos_c);
      max = FastBVH::max(max, pos_c);

      min_x[i] = min.x;
      min_y[i] = min.y;
      min_z[i] = min.z;

      max_x[i] = max.x;
      max_y[i] = max.y;
      max_z[i] = max.z;
    }
  }

  //! Converts a face to a bounding box.
  //! \param face_index The index of the face to get the bounding box of.
  //! \return The bounding box that fits the specified face.
  FastBVH::BBox<float> operator()(std::size_t face_index) const noexcept {

    FastBVH::Vector3<float> min{
        min_x[face_index],
        min_y[face_index],
        min_z[face_index],
    };

    FastBVH::Vector3<float> max{
        max_x[face_index],
        max_y[face_index],
        max_z[face_index],
    };

    return FastBVH::BBox<float>(min, max);
  }
};

} // namespace Benchmark

} // namespace FastBVH
